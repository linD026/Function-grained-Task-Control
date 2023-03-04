#include <ftc/transfer.h>
#include <ftc/debug.h>
#include <getopt.h>
#include <string.h>

#undef pr_log_fmt
#define pr_log_fmt "init"

struct transfer transfer = {
    .input = "set_ftc_source_code",
    .compiler = "gcc",
};

#define OPT_COMPILER 0
#define NR_OPTION 1
#define OPT_STRING "0"

struct opt_data {
    unsigned int flags[NR_OPTION];
    struct option options[NR_OPTION];
};

static struct opt_data opt_data = {
    .flags = { 0 },
    .options = { 
        { "CC", optional_argument, 0, OPT_COMPILER },
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
        default:
            BUG_ON(1, "unkown option: %d", opt);
        }
    }
}

int main(int argc, char *argv[])
{
    set_option(argc, argv);
    dump_transfer();

    return 0;
}
