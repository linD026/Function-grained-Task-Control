#ifndef __FTC_TASK_H__
#define __FTC_TASK_H__

#ifndef FILENAME_SIZE
#define FILENAME_SIZE 80
#endif

struct task_struct {
    char name[FILENAME_SIZE];
};

int execute_task(struct task_struct *task);

#endif /* __FTC_TASK_H__ */
