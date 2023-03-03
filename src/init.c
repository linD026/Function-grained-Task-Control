#include <mthpc/rcu.h>
#include <mthpc/print.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("hello world\n");
    mthpc_pr_info("mthpc library hello world\n");
    mthpc_rcu_read_lock();
    mthpc_rcu_read_unlock();

    return 0;
}
