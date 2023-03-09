#ifndef __FTC_TASK_H__
#define __FTC_TASK_H__

#include <mthpc/workqueue.h>

#ifndef FILENAME_SIZE
#define FILENAME_SIZE 80
#endif

struct task_struct {
    char name[FILENAME_SIZE + FILENAME_SIZE];
    unsigned long id;
    struct mthpc_work work;
};

void execute_task(struct mthpc_work *work);

#endif /* __FTC_TASK_H__ */
