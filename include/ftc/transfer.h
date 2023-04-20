#ifndef __TRANSFER_H__
#define __TRANSFER_H__

#ifndef FILENAME_SIZE
#define FILENAME_SIZE 80
#endif

#ifndef BUFFER_SIZE
#define BUFFFER_SIZE 80
#endif

#if __linux__
#include <sys/epoll.h>
#include <sys/inotify.h>

#ifndef NR_EPOLL_EVENT
/*
 * Use case:
 * index 0: set_ftc_source_code
 */
#define NR_EPOLL_EVENT 4
#endif

struct file_event {
    char name[FILENAME_SIZE];
    int fd;
    struct transfer_epoll {
        int fd;
        struct epoll_event event;
        struct epoll_event events[NR_EPOLL_EVENT];
    } epoll;
    struct transfer_inotify {
        int fd;
        int watch_point;
    } inotify;
    void (*event_handler)(struct file_event *);
    void *arg;
};

#else
#include <assert.h>
static_assert(
    0, "Unsupport inotify "
       "TODO: For BSD, use kqueue - kernel event notification mechanism");
#endif

#include <stdatomic.h>

#define CFLAGS_MAX_SIZE 16

struct transfer {
    char compiler[FILENAME_SIZE];
    struct {
        unsigned int nr_cflags;
        char cflags[CFLAGS_MAX_SIZE][BUFFFER_SIZE];
    };
    struct file_event event_set_source_code;
    atomic_ulong task_count;
};

/* define at src/init.c */
extern struct transfer transfer;

void dump_transfer(void);

int setup_files(void);
void unset_files(void);
void wait_file_event(struct file_event *fe);

#endif /* __TRANSFER_H__ */
