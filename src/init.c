#include <ftc/transfer.h>
#include <ftc/debug.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

#undef pr_log_fmt
#define pr_log_fmt "init"

struct transfer transfer = {
    .compiler = "gcc",
    .cflags = "-Wall -O2",
};

#define OPT_COMPILER 0
#define OPT_CFLAGS 1
#define NR_OPTION 2
#define OPT_STRING "01"

struct opt_data {
    unsigned int flags[NR_OPTION];
    struct option options[NR_OPTION];
};

static struct opt_data opt_data = {
    .flags = { 0 },
    .options = { 
        { "CC", optional_argument, 0, OPT_COMPILER },
        { "CFLAGS", optional_argument, 0, OPT_CFLAGS },
    },
};

static void set_option(int argc, char *argv[])
{
    int opt;
    int opt_index;

    while ((opt = getopt_long(argc, argv, OPT_STRING, opt_data.options,
                              &opt_index)) != -1) {
        switch (opt) {
        case OPT_COMPILER:
            strncpy(transfer.compiler, optarg, FILENAME_SIZE);
            transfer.compiler[FILENAME_SIZE - 1] = '\0';
            break;
        case OPT_CFLAGS:
            strncpy(transfer.cflags, optarg, BUFFFER_SIZE);
            transfer.cflags[BUFFFER_SIZE - 1] = '\0';
            break;
        default:
            BUG_ON(1, "unkown option: %d", opt);
        }
    }
}

static struct sigaction sa;

static void cleanup_handler(int sig, siginfo_t *si, void *unused)
{
#undef pr_log_fmt
#define pr_log_fmt "signal"

    pr_log("Exiting the program...\n");
    pr_log("Cleanup the settings...\n");
    unset_files();
    exit(EXIT_SUCCESS);

#undef pr_log_fmt
#define pr_log_fmt "init"
}

static void setup_signal(void)
{
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = cleanup_handler;
    BUG_ON(sigaction(SIGINT, &sa, NULL) == -1, "signal handler");
}

int main(int argc, char *argv[])
{
    set_option(argc, argv);
    pr_log("Transfer iniitization\n");
    dump_transfer();
    setup_files();
    setup_signal();
    wait_file_event(&transfer.event_set_source_code);
    unset_files();

    return 0;
}
