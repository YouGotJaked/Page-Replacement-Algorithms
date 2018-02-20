/*
maintain linked list of all pages
maintain order in which pages entered memory
replace page at front of list
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.c>
#include "deque.h"
#include "helper.h"

#define SIZE 1024

int main (int argc, char **argv) {
	// check argument count
	if (check_argc(argc, 2, argv[0]) != 2) {
		return -1;
	}

	
