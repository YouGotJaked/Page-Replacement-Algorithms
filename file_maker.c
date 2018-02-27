#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

#define SIZE atoi(argv[2])
#define REPEAT atoi(argv[3])

int main(int argc, char **argv) {
	check_argc(argc, 4, argv, 1);

	FILE *fp;
	fp = fopen(argv[1], "w");

	if (fp == NULL)
		return -1;

	for (int i = 0; i < REPEAT; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == REPEAT - 1 && j == SIZE - 1) {
				fprintf(fp, "%d", j + 1);
			} else {
				fprintf(fp, "%d\n", j + 1);
			}
		}
	}
	fclose(fp);
	return 0;
}
