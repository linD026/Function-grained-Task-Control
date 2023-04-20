#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <spawn.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>

#define USEC 1000000
#define N_LOOP 1000

int lw_system(char *restrict exec, char *argv[])
{
    int ret = 0;
    pid_t child_pid = 0;
    posix_spawnattr_t attr;
    extern char **environ;

    posix_spawnattr_init(&attr);
    posix_spawnattr_setflags(&attr, POSIX_SPAWN_USEVFORK);

    ret = posix_spawn(&child_pid, argv[0], NULL, &attr, argv, environ);

    if (ret) {
        printf("posix_spawn:%d pid:%d error:%s\n", ret, child_pid,
               strerror(ret));
        return ret;
    }

    ret = waitpid(child_pid, &ret, 0);

    return ret != -1 ? 0 : -1;
}

#define SIZE 4096 * 10

int main(void)
{
    struct timeval start, end;
    long duration;
    const char *cmd = "gcc -o test compile_benchmark.c -Wall -O2";
    char *argv[] = {
        "/usr/bin/gcc", "-o",  "test", "compile_benchmark.c",
        "-Wall",        "-O2", NULL,
    };
    int page_size = getpagesize();
    char *dummy = mmap(NULL, SIZE, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < SIZE; i += page_size)
        dummy[i] = 0;

    gettimeofday(&start, NULL);
    for (int i = 0; i < N_LOOP; i++)
        system(cmd);
    gettimeofday(&end, NULL);
    duration =
        ((end.tv_sec - start.tv_sec) * USEC + (end.tv_usec - start.tv_usec)) /
        N_LOOP;
    printf("system: %ld.%06ld seconds\n", duration / USEC, duration % USEC);

    gettimeofday(&start, NULL);
    for (int i = 0; i < N_LOOP; i++)
        lw_system("/usr/bin/gcc", argv);
    gettimeofday(&end, NULL);
    duration =
        ((end.tv_sec - start.tv_sec) * USEC + (end.tv_usec - start.tv_usec)) /
        N_LOOP;
    printf("posix_spawn: %ld.%06ld seconds\n", duration / USEC,
           duration % USEC);

    return 0;
}
