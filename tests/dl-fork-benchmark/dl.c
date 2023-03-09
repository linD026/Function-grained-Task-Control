#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/time.h>

#define USEC 1000000
#define N_LOOP 1000

#ifndef CURR_DIR
#define CURR_DIR ""
#endif

#define FILE_CURRENT_PATH(name) CURR_DIR "/" name

int main(void)
{
    struct timeval start, end;
    long duration;
    void *dl = NULL;
    void (*handle)(void);

    gettimeofday(&start, NULL);
    for (int i = 0; i < N_LOOP; i++) {
        system("gcc -o libuser.so user.c -Wall -O2 -shared");
        dl = dlopen(
            FILE_CURRENT_PATH("libuser.so"),
            RTLD_LAZY);
        handle = (void (*)(void))dlsym(dl, "test");
        handle();
        dlclose(dl);
    }
    gettimeofday(&end, NULL);
    duration =
        ((end.tv_sec - start.tv_sec) * USEC + (end.tv_usec - start.tv_usec)) /
        N_LOOP;
    printf("dl: %ld.%06ld seconds\n", duration / USEC, duration % USEC);
}
