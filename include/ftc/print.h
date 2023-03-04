#ifndef ___PRINT_H__
#define ___PRINT_H__

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#define debug_stream stdout
#define err_stream stderr

static inline struct timeval ___get_us(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return tv;
}

#define print(fmt, ...)                            \
    do {                                           \
        fprintf(debug_stream, fmt, ##__VA_ARGS__); \
    } while (0)

#define pr_info(fmt, ...)                                                    \
    do {                                                                     \
        struct timeval __pr_tv = ___get_us();                                \
        print("\e[32m[%5lu.%06lu]\e[0m %s:%d:%s: " fmt, __pr_tv.tv_sec,      \
              __pr_tv.tv_usec, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define pr_err(fmt, ...)                                                     \
    do {                                                                     \
        struct timeval __pr_tv = ___get_us();                                \
        fprintf(err_stream,                                                  \
                "\e[32m[%5lu.%06lu] [TASK %lx]\e[0m %s:%d:%s: "              \
                "\e[31m" fmt "\e[0m",                                        \
                __pr_tv.tv_sec, __pr_tv.tv_usec,                             \
                (unsigned long)pthread_self(), __FILE__, __LINE__, __func__, \
                ##__VA_ARGS__);                                              \
    } while (0)

#define pr_log_fmt ""

#define pr_log(fmt, ...)                                           \
    do {                                                           \
        struct timeval __pr_tv = ___get_us();                      \
        if (pr_log_fmt[0] == '\0')                                 \
            print("\e[32m[%5lu.%06lu]\e[0m " fmt, __pr_tv.tv_sec,  \
                  __pr_tv.tv_usec, ##__VA_ARGS__);                 \
        else                                                       \
            print("\e[32m[%5lu.%06lu] " pr_log_fmt "\e[0m: " fmt,  \
                  __pr_tv.tv_sec, __pr_tv.tv_usec, ##__VA_ARGS__); \
    } while (0)

#endif /* __PRINT_H__ */
