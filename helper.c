#include "helper.h"

int check_argc(int argc, int n, char *exec) {
	if (argc != n) {
		fprintf(stderr, "Usage: %s <page table size>\n", exec);
		exit(-1);
	}
	return n;
}
