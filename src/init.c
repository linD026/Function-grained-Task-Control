#include <ftc/transfer.h>
#include <ftc/debug.h>
#include <getopt.h>
#include <string.h>

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

int main(int argc, char *argv[])
{
    set_option(argc, argv);
    pr_log("Transfer iniitization\n");
    dump_transfer();
    setup_files();
    wait_file_event(&transfer.event_set_source_code);
    unset_files();

    return 0;
}
