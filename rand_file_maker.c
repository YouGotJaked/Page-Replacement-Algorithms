#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"

#define SIZE atoi(argv[2])
#define LO atoi(argv[3])
#define HI atoi(argv[4])

int main(int argc, char **argv) {
    check_argc(argc, 5, argv, 2);
    
    FILE *fp;
    fp = fopen(argv[1], "w");
    
    if (fp == NULL)
        return -1;
    
    int r;
    srand(time(NULL));
    
    for (int i = 0; i < SIZE; i++) {
        r = rand() % (HI + 1 - LO) + LO;
        if (i == SIZE - 1) {
            fprintf(fp, "%d", r);
        } else {
            fprintf(fp, "%d\n", r);
        }
    }
    fclose(fp);
    return 0;
}

