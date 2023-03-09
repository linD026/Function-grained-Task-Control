#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    pid_t ret;

    gettimeofday(&start, NULL);
    for (int i = 0; i < N_LOOP; i++) {
        system("gcc -o fork-user user.c -Wall -O2");
        ret = fork();
        if (ret == 0)
            execl(FILE_CURRENT_PATH("fork-user"), "fork", (char*) NULL);
        else if (ret > 0)
            waitpid(ret, NULL, 0);
    }
    gettimeofday(&end, NULL);
    duration =
        ((end.tv_sec - start.tv_sec) * USEC + (end.tv_usec - start.tv_usec)) /
        N_LOOP;
    printf("Fork: %ld.%06ld seconds\n", duration / USEC, duration % USEC);
}
