#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <ftc/print.h>
#include <ftc/util.h>
#include <stdlib.h>
#include <execinfo.h>

static __always_inline void dump_stack(void)
{
#define STACK_BUF_SIZE 32
    char **stack_info;
    int nr = 0;
    void *buf[STACK_BUF_SIZE];

    nr = backtrace(buf, STACK_BUF_SIZE);
    stack_info = backtrace_symbols(buf, nr);

    print("========== dump stack start ==========\n");
    for (int i = 0; i < nr; i++)
        print("  %s\n", stack_info[i]);
    print("========== dump stack  end  ==========\n");
#undef STACK_BUF_SIZE
}

#define BUG_ON(cond, fmt, ...)                                     \
    do {                                                           \
        if (unlikely(cond)) {                                      \
            pr_err("BUG ON: " #cond ", " fmt "\n", ##__VA_ARGS__); \
            dump_stack();                                          \
            exit(EXIT_FAILURE);                                    \
        }                                                          \
    } while (0)

#define WARN_ON(cond, fmt, ...)                                    \
    do {                                                           \
        if (unlikely(cond))                                        \
            pr_err("WARN ON:" #cond ", " fmt "\n", ##__VA_ARGS__); \
    } while (0)

#endif /* __DEBUG_H__*/
