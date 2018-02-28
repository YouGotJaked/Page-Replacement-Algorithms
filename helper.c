#include "helper.h"

/*
 * INDEX KEY
 * 0: page replacement algorithms
 * 1: sequential test files
 * 2: random test file
 */

const char *help_txt[] = {
    "<page table size>\n",
    "<file name> <size> <repeat>\n",
    "<file name> <size> <lo> <hi>\n",
};

int check_argc(int argc, int n, const char **argv, int idx) {
    if (argc != n) {
        fprintf(stderr, "Usage: %s %s", argv[0], help_txt[idx]);
        exit(-1);
    }
    return n;
}
