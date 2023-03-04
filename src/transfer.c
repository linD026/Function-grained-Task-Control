#include <ftc/transfer.h>
#include <ftc/task.h>
#include <ftc/debug.h>
#include <dlfcn.h>

#undef pr_log_fmt
#define pr_log_fmt "transfer"

void dump_transfer(void)
{
    pr_log("input file: %s\n", transfer.input);
    pr_log("compiler: %s\n", transfer.compiler);
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
