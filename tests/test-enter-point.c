#include <stdio.h>
#include "../include/uapi/ftc.h"

int dummy(int a)
{
    a = 1;
    return a;
}

FTC_ENTER_POINT(test) {
    int a = 0;
    a+=1;
    a = 2 + dummy(a);
}
