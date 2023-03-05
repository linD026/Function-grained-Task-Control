#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define USEC 1000000
#define N_LOOP 1000

int main(void)
{
    struct timeval start, end;
    long duration;

    gettimeofday(&start, NULL);
    for (int i = 0; i < N_LOOP; i++) {
        system("gcc -o fork-user user.c -Wall -O2");
        system("./fork-user");
    }
    gettimeofday(&end, NULL);
    duration =
        ((end.tv_sec - start.tv_sec) * USEC + (end.tv_usec - start.tv_usec)) /
        N_LOOP;
    printf("Fork: %ld.%06ld seconds\n", duration / USEC, duration % USEC);
}
