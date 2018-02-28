/*
 at each clock interrupt, scan through table
if R=1 for page, add 1 to counter
on replacement, pick page with lowest counter
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "deque.h"
#include "helper.h"

#define SIZE 100

int main(int argc, char **argv) {
    // check arguments
    check_argc(argc, 2, argv, 0);
    
    char buffer[SIZE];
    int page_frames = atoi(argv[1]);
    int count_memory = 0;
    int count_fault = 0;
    int cycles = 0;
    
    // use deque to create page table
    DEQUE *page_table = createDeque();
    
    while(fgets(buffer, SIZE, stdin) != NULL) {
        int curr_page;
        // get first number on line
        int page_val = sscanf(buffer, "%d", &curr_page);
        // only access if number
        if (page_val > 0) {
            cycles++;
            count_memory++;
            // do ??? if page already in table
            if (findNode(page_table, curr_page) != NULL) {
                printf("Found node at %d\n", curr_page);
                setTime(page_table, curr_page, cycles);
            } // remove least used page if table is full
            else if (numItems(page_table) == page_frames) {
                removeLeastUsed(page_table);
                addLast(page_table, curr_page);
                setLastTime(page_table, cycles);
                count_fault++;
                fprintf(stderr, "PAGE FAULT: %d\n", curr_page);
            } else {
                addLast(page_table, curr_page);
                setLastTime(page_table, cycles);
            }
        }
        printDeque(page_table);
    }
    printf("Memory accesses: %d\n", count_memory);
    printf("Page faults: %d\n", count_fault);
}
