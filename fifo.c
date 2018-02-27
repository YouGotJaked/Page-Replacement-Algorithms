/*
maintain linked list of all pages
maintain order in which pages entered memory
replace page at front of list
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "deque.h"
#include "helper.h"

#define SIZE 1024

int main (int argc, char **argv) {
	// check arguments
	check_argc(argc, 2, argv);

	char buffer[SIZE];
	int page_frames = atoi(argv[1]);
	int count_fault = 0;
	int count_memory = 0;
	
	// use deque to create page table
	DEQUE *page_table = createDeque();

	while (fgets(buffer, SIZE, stdin) != NULL) {
		// get first number on line
		// only access page if number
			// do nothing if page already in table
			// add page to queue if room otherwise find page to remove
				// find and replace page
					// move node with value of first to tail
				// remove first node
				// add new node to tail
			// if room place page at tail

}
	
