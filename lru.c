/*
keep linked list of pages
most recently used page at front, least at rear
update list of pages every memory reference
assume pages used recently will be used again soon
can also keep counter in each page table entry
increment counter with each CPU cycle (how to sim?)
copy counter to PTE counter on reference to page
evict page with lowest counter value
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "deque.h"
#include "helper.h"

#define SIZE 1024

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
                setTime(page_table, curr_page, cycles);
            } // remove page with oldest time if table is full
            else if (numItems(page_table) == page_frames) {
                removeOldestTime(page_table);
                addLast(page_table, curr_page);
                setLastTime(page_table, cycles);
                count_fault++;
                fprintf(stderr, "PAGE FAULT: %d\n", curr_page);
            } else {
                addLast(page_table, curr_page);
                setLastTime(page_table, cycles);
                count_fault++;
            }
        }
        printDeque(page_table);
    }
    printf("Memory accesses: %d\n", count_memory);
    printf("Page faults: %d\n", count_fault);
}
