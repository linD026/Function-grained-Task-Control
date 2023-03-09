#include <ftc/task.h>
#include <ftc/print.h>
#include <ftc/debug.h>
#include <sys/time.h>
#include <dlfcn.h>
#include <stdio.h>

#undef pr_log_fmt
#define pr_log_fmt "task"

#define time_diff(start, end)                         \
    (end.tv_nsec - start.tv_nsec < 0 ?                \
         (1000000000 + end.tv_nsec - start.tv_nsec) : \
         (end.tv_nsec - start.tv_nsec))

int execute_task(struct task_struct *task)
{
    struct timespec start, end;
    double duration;
    void *dl = NULL;
    void (*handle)(void);
    char task_enter_point[FILENAME_SIZE] = { 0 };
    char *error = NULL;

    sprintf(task_enter_point, "ftc_%lu_enter_point", task->id);
    task_enter_point[FILENAME_SIZE - 1] = '\0';

    dl = dlopen(task->name, RTLD_LAZY);
    if (!dl) {
        WARN_ON(1, "%s: %s", task->name, dlerror());
        return -1;
    }
    handle = (void (*)(void))dlsym(dl, task_enter_point);
    if (error) {
        WARN_ON(1, "dlsym(%s):%s", task_enter_point, error);
        return -1;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    handle();
    clock_gettime(CLOCK_MONOTONIC, &end);
    dlclose(dl);
    duration = time_diff(start, end);
    pr_log("%s (%lu) executed %.6f ns\n", task->name, task->id, duration);

    return 0;
}
