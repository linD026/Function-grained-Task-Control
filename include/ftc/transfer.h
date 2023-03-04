#ifndef __TRANSFER_H__
#define __TRANSFER_H__

#include <stdio.h>

#ifndef FILENAME_SIZE
#define FILENAME_SIZE 80
#endif

struct transfer {
    char input[FILENAME_SIZE];
    FILE *fp;
    char compiler[FILENAME_SIZE];
    // epoll notify someone write the runtime lib to the fp.
};

/* define at src/init.c */
extern struct transfer transfer;

void dump_transfer(void);

#endif /* __TRANSFER_H__ */
