#include <ftc/transfer.h>
#include <ftc/task.h>
#include <ftc/debug.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h> // for close()
#include <errno.h>
#include <string.h> // for strerror

#undef pr_log_fmt
#define pr_log_fmt "transfer"

void dump_transfer(void)
{
    // TODO: dump_file_event
    pr_log("input file: %s\n", transfer.event_set_source_code.name);
    pr_log("compiler: %s\n", transfer.compiler);
    pr_log("cflags: %s\n", transfer.cflags);
}

static int setup_file_event(struct file_event *fe, const char *name,
                            void (*event_handler)(struct file_event *))
{
    BUG_ON(!fe || !name || !event_handler, "NULL ptr");

    strncpy(fe->name, name, min(strlen(name), FILENAME_SIZE));
    fe->fd = open(fe->name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    lseek(fe->fd, 0, SEEK_SET);

    fe->inotify.fd = inotify_init1(IN_NONBLOCK);
    fe->inotify.watch_point =
        inotify_add_watch(fe->inotify.fd, fe->name, IN_CLOSE_WRITE);
    BUG_ON(fe->inotify.watch_point == -1, "cannot watch %s: %s", fe->name,
           strerror(errno));

    fe->epoll.fd = epoll_create1(0);
    fe->epoll.event.data.fd = fe->inotify.fd;
    fe->epoll.event.events = EPOLLIN | EPOLLET;
    BUG_ON(epoll_ctl(fe->epoll.fd, EPOLL_CTL_ADD, fe->inotify.fd,
                     &fe->epoll.event) == -1,
           "epoll_ctl: inotify_fd");

    fe->event_handler = event_handler;
    fe->arg = NULL;

    return 0;
}

// TODO: Add singal handler
static void unset_file_event(struct file_event *fe)
{
    close(fe->fd);
    close(fe->inotify.fd);
}

static int epoll_event_handler(struct file_event *fe,
                               struct epoll_event *epoll_event)
{
    /* set_ftc_source_code file */
    if (epoll_event->data.fd == fe->inotify.fd) {
        char buf[4096]
            __attribute__((aligned(__alignof__(struct inotify_event))));
        const struct inotify_event *inotify_event;
        ssize_t len;

        for (;;) {
            len = read(epoll_event->data.fd, buf, sizeof(buf));
            BUG_ON(len == -1 && errno != EAGAIN, "read");
            if (len <= 0)
                return -EAGAIN;
            for (char *ptr = buf; ptr < buf + len;
                 ptr += sizeof(struct inotify_event) + inotify_event->len) {
                inotify_event = (const struct inotify_event *)ptr;
                if (inotify_event->mask & IN_CLOSE_WRITE) {
                    fe->event_handler(fe);
                    return 0;
                }
            }
        }
    }
    return -EAGAIN;
}

void wait_file_event(struct file_event *fe)
{
    for (;;) {
        int nfds =
            epoll_wait(fe->epoll.fd, fe->epoll.events, NR_EPOLL_EVENT, -1);
        WARN_ON(nfds == -1, "epoll_wait");
        for (int i = 0; i < nfds; i++) {
            struct epoll_event *epoll_event = &fe->epoll.events[i];
            epoll_event_handler(fe, epoll_event);
        }
    }
}

static struct task_struct *get_user_program(void)
{
    struct task_struct *task = NULL;

    task = malloc(sizeof(struct task_struct));
    if (!task) {
        WARN_ON(1, "allocate failed for the memory of user program info\n");
        return NULL;
    }

    return task;
}

static void event_set_source_code_handler(struct file_event *fe)
{
    ssize_t ret;
    char buffer[BUFFFER_SIZE] = { 0 };

    pr_log("file event: set_source_code\n");
    ret = read(fe->fd, buffer, BUFFFER_SIZE);
    BUG_ON(ret == -1 && errno != EAGAIN, "read");

    buffer[BUFFFER_SIZE - 1] = '\0';
    pr_log("Read %s: %s", fe->name, buffer);
    lseek(fe->fd, 0, SEEK_SET);
    /* TODO: create task */
    // TODO: Build the task
    // TODO: Add the task to the workqueue
}

int setup_files(void)
{
    int ret;
    ret =
        setup_file_event(&transfer.event_set_source_code, "set_ftc_source_code",
                         event_set_source_code_handler);
    return ret;
}

void unset_files(void)
{
    unset_file_event(&transfer.event_set_source_code);
}
