/*
maintain linked list of all pages
maintain order in which pages entered memory
replace page at front of list
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "deque.h"
#include "helper.h"

#define SIZE 1024

int main (int argc, char **argv) {
	// check arguments
	check_argc(argc, 2, argv, 0);

	char buffer[SIZE];
	int page_frames = atoi(argv[1]);
    int count_memory = 0;
	int count_fault = 0;
	
	// use deque to create page table
	DEQUE *page_table = createDeque();

	while (fgets(buffer, SIZE, stdin) != NULL) {
        int curr_page;
		// get first number on line
        int page_val = sscanf(buffer, "%d", &curr_page);
		// only access page if number
        if (page_val > 0) {
            count_memory++;
			// do nothing if page already in table
            if (findNode(page_table, curr_page) != NULL) {
                // ???
            } // remove first page if table is full
            else if (numItems(page_table) == page_frames) {
                removeFirst(page_table);
                // add new node at tail
                addLast(page_table, curr_page);
                count_fault++;
                fprintf(stderr, "PAGE FAULT: %d\n", curr_page);
            } // add page to queue if room
            else {
                addLast(page_table, curr_page);
            }
        }
        printDeque(page_table);
    }
    printf("Memory accesses: %d\n", count_memory);
    printf("Page faults: %d\n", count_fault);
}
	
