#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "deque.h"

typedef struct node {
  	struct node *prev;	
	struct node *next;	
	int data;		
	int used;
	int time;	
} NODE;

typedef struct deque {
	struct node *dummy;
	int count;
} DEQUE;


DEQUE *createDeque(void) {
	DEQUE *dp = (DEQUE *)malloc(sizeof(DEQUE));
	assert(dp != NULL);
	dp->dummy = malloc(sizeof (NODE));
	assert(dp->dummy != NULL);
	/*Link the dummy node to itself */
	dp->dummy->next = dp->dummy;
	dp->dummy->prev = dp->dummy;

	/*Sentinel node contains no data, so it does not count towards count*/
	dp->count = 0;
	return dp;
}
void destroyDeque(DEQUE *dp) {
	assert(dp != NULL);
	NODE * head = dp->dummy->next;
	NODE * temp;
	/* 
	 * If dp->dummy->next == NULL, then dp->dummy is the only thing to free and the while loop wont run
	 * Want the while loop to go through the list and delete all nodes until it circles back and hits the dummy, as that marks the end of the circle
	 * Free the dummy outside of the loop and then free the deque
	*/
	while (head != NULL && head != dp->dummy) {
		temp = head;
		head = head->next;
		free(temp);
	}//end while
	free(dp->dummy);
	free(dp);
	return;
}

int numItems(DEQUE * dp) {
	return dp->count;
}

void addFirst (DEQUE *dp, int x) {
	assert(dp != NULL);
	/*Allocate memory for a new node and then assert that it was allocated correctly*/
	NODE * np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->data = x;
	np->used = 0;
	np->time = 0;
	/* Insert the new node into the circular doubly linked list directly after the dummy(dummy->next = np).*/
	dp->dummy->next->prev = np;
	np->next = dp->dummy->next;
	np->prev = dp->dummy;
	dp->dummy->next = np;
	dp->count++;
}

void addLast(DEQUE *dp, int x) {
	assert(dp != NULL);
	NODE * np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->data = x;
	np->used = 0;
	np->time = 0;
	/*Insert the new node after the dummy (dummy->prev = np)*/
	dp->dummy->prev->next = np;
	np->prev = dp->dummy->prev;
	np->next = dp->dummy;
	dp->dummy->prev = np;
	dp->count++;
}

int removeFirst(DEQUE *dp) {
	assert(dp != NULL);
	/*If the dummy is the only node in the deque, then there is nothing to remove and return*/
	if (dp->count == 0)
		return -1;
	/*Return the data (int) from the node after dummy (dummy->next) and reassign pointers*/
	int data = dp->dummy->next->data;
	NODE *np = dp->dummy->next; //temporary copy
	dp->dummy->next = np->next;
	np->next->prev = dp->dummy;
	free(np);
	dp->count--;
	return data;
}

int removeLast(DEQUE *dp) {
	assert(dp != NULL);
	/*If the dummy is the only node in the deque, then there is nothing to remove and return*/
	if (dp->dummy->next == NULL)
		return - 1;
	/*Return the data (int) from the node before dummy (dummy->prev) and reassign pointers*/
	int data = dp->dummy->prev->data;
	NODE *np = dp->dummy->prev; //temporary copy
	dp->dummy->prev = np->prev;
	np->prev->next = dp->dummy;
	free(np);
	dp->count--;
	return data;
}

int getFirst (DEQUE *dp) {
	assert(dp != NULL);
	if (dp->dummy->next == NULL)
		return -1;
	return dp->dummy->next->data;
}

 int getLast (DEQUE *dp) {
	assert(dp != NULL);
	if (dp->dummy->next == NULL)
		return -1;
	return dp->dummy->prev->data;
 }
 
NODE* findNode(DEQUE *dp, int x) { 
	int found = 0;
	NODE* np = dp->dummy->next;
	while (np != dp->dummy) {
		if (np->data == x) {
			//if the page is already in the list, do nothing
			found = 1;
			break;
		}
		np = np->next;
	}
	if (found == 1)
		return np;
	else
		return NULL;
}

void setTime(DEQUE *dp, int x, int time) {
	NODE* np = findNode(dp, x);
	np->time = time;
	np->used++;
}

void setLastTime(DEQUE *dp, int time) {
	assert(dp != NULL);	
	dp->dummy->prev->time = time;
	dp->dummy->prev->used++;
}

void moveToFront(DEQUE *dp, int x) {
	assert(dp != NULL);
			
	/*If the dummy is the only node in the deque, then there is nothing to remove and return*/
	if (dp->dummy->next == NULL)
		return;

	//find the node
	NODE* n = findNode(dp,x);
	if (n == NULL)
		return;

	//break the list chain around n
	n->prev->next = n->next;
	n->next->prev = n->prev;
	
	//insert n in the front of the list
	n->prev = dp->dummy;
	n->next = dp->dummy->next;
	dp->dummy->next->prev = n;
	dp->dummy->next = n;
	return;	
}

void removeOldestTime(DEQUE* dp) {
        assert(dp != NULL);

        if (dp->dummy->next == NULL)
                return;

        NODE* np = dp->dummy->next;
        NODE* least = np;
	//search for lowest time
        while (np != dp->dummy) {
                if (np->time < least->time) {
                        least = np;
                }
		np = np->next;
        }
	//remove lowest time
        least->prev->next = least->next;
        least->next->prev = least->prev;
        free(least);
        dp->count--;
}

void removeLeastUsed(DEQUE *dp) {

	assert(dp!=NULL);
	if (numItems(dp) == 0)
		return;

	
	NODE* np = dp->dummy->next;
	NODE* least = np;
	
	//search for node with the lowest "used" counter.
	//if there is a tie, remove the one used furthest in the past
	while (np != dp->dummy) {
		if (np->used < least->used) {
			least = np;
		}
		else if (np->used == least->used) {
			if (np->time < least->time) {
				least = np;
			}
		}
		np = np->next;
	}
	//remove lowest time
        least->prev->next = least->next;
        least->next->prev = least->prev;
        free(least);
        dp->count--;

}

void removeRandom(DEQUE *dp) {
	assert(dp != NULL);
	
	srand(time(NULL));
	
	int i;
	NODE *np = dp->dummy->next;
	NODE *rand_page = np;
	
	for (i = 2; i < dp->count; i++) {
		if (rand() % i == 0) {
		  printf("res: %d mod %d\n", rand(), i);
			rand_page = np;
		}
		np = np->next;
	}
	moveToFront(dp, rand_page->data);
	removeFirst(dp);
}

void printDeque(DEQUE *dp) {
	NODE* np = dp->dummy->next;

	while (np != dp->dummy) {
		printf("data:%d; used: %d; time: %d\n",np->data, np->used, np->time);
		np = np->next;
	}
	printf("------------------------------\n");
}