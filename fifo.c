#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "deque.h"
#include "helper.h"

#define SIZE 1024

int main (int argc, const char* argv[]) {
	// check arguments
	check_argc(argc, 2, argv, 0);

	char buffer[SIZE];
	int page_frames = atoi(argv[1]);
	int page_reqs = 0;
	int page_faults = 0;

	// use deque to create page table
	DEQUE* page_table = createDeque();
	

	//loop through the file and grab the numbers in there
	while (fgets(buffer, SIZE, stdin) != NULL ) {
		int curr_page;
		// get first number on line
		int page_val = sscanf(buffer, "%d", &curr_page);
		// only access page if number
		if (page_val > 0){
			page_reqs++;
			// do nothing if page already in table
			if (findNode(page_table, curr_page) != NULL) {
				//setRef(page_table,access);
			} // remove first page if table is full
			else if (numItems(page_table) ==  page_frames) {
				removeFirst(page_table);			
				//add new page at tail
				addLast(page_table, curr_page);
				page_faults++;	
				fprintf(stderr, "PAGE FAULT: %d\n", curr_page);
			} // add page if room
			else {
				addLast(page_table, curr_page);
				
			}
		
		}
		printDeque(page_table);
	}
	printf("page requests: %d\n", page_reqs);
	printf("page faults: %d\n",page_faults);	
}
