#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <spawn.h>
#include <ftc/transfer.h>
#include <ftc/util.h>
#include <ftc/debug.h>
#include <ftc/print.h>

int __lw_system(char *restrict exec, char *argv[])
{
    int ret = 0;
    pid_t child_pid = 0;
    posix_spawnattr_t attr;
    extern char **environ;

    /* TODO: Add error handling instead of using the BUG_ON. */
    BUG_ON(posix_spawnattr_init(&attr), "init attr");
    BUG_ON(posix_spawnattr_setflags(&attr, POSIX_SPAWN_USEVFORK), "set attr");

    ret = posix_spawn(&child_pid, argv[0], NULL, &attr, argv, environ);

    if (unlikely(ret)) {
        pr_log("posix_spawn:%d pid:%d error:%s\n", ret, child_pid,
               strerror(ret));
        WARN_ON(1, "posix_spawn failed");
        return ret;
    }

    ret = waitpid(child_pid, &ret, 0);
    WARN_ON(ret == -1, "waitpid");

    return ret != -1 ? 0 : -1;
}
