#ifndef __FTC_TASK_H__
#define __FTC_TASK_H__

#define FILENAME_SIZE 80

struct task_struct {
    char filename[FILENAME_SIZE];
    unsigned int id;
};

#endif /* __FTC_TASK_H__ */
