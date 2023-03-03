#ifndef ___PRINT_H__
#define ___PRINT_H__

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#define debug_stream stdout
#define err_stream stderr

static inline unsigned long ___get_us(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (unsigned long)1000000 * tv.tv_sec + tv.tv_usec;
}

#define print(fmt, ...)                            \
    do {                                           \
        fprintf(debug_stream, fmt, ##__VA_ARGS__); \
    } while (0)

#define pr_info(fmt, ...)                                                  \
    do {                                                                   \
        print("\e[32m[%-10lu]\e[0m %s:%d:%s: " fmt, ___get_us(), __FILE__, \
              __LINE__, __func__, ##__VA_ARGS__);                          \
    } while (0)

#define pr_err(fmt, ...)                                              \
    do {                                                              \
        fprintf(err_stream,                                           \
                "\e[32m[%-10lu] [TASK %lx]\e[0m %s:%d:%s: "           \
                "\e[31m" fmt "\e[0m",                                 \
                ___get_ms(), (unsigned long)pthread_self(), __FILE__, \
                __LINE__, __func__, ##__VA_ARGS__);                   \
    } while (0)

#endif /* __PRINT_H__ */
