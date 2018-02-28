#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"

typedef struct node {
    struct node *next;
    struct node *prev;
    int data;
    int time;
    int used;
} NODE;

typedef struct deque {
    int count;
    struct node *dummy;
} DEQUE;

/*
 * Big-O Notation: O(1)
 * Returns a pointer to a new deque
 */
DEQUE *createDeque(void) {
    DEQUE *dp;

    dp = malloc(sizeof (DEQUE));
    assert(dp != NULL);

    dp->count = 0;

    dp->dummy = malloc(sizeof (struct node));
    assert(dp->dummy != NULL);

    dp->dummy->next = dp->dummy;
    dp->dummy->prev = dp->dummy;

    return dp;
}

/*
 * Big-O Notation: O(n)
 * Deallocates memory associated with the deque pointed to by dp
 */

void destroyDeque(DEQUE *dp) {
    assert(dp != NULL);

    struct node *pDel;

    for (int i = 0; i < dp->count; i++) {
        pDel = dp->dummy->next;
        dp->dummy->next = pDel->next;
        free(pDel);
    }
}

/*
 * Big-O Notation: O(1)
 * Returns the number of items in the deque pointed to by dp
 */
int numItems(DEQUE *dp) {
    assert(dp != NULL);

    return dp->count;
}

/*
 * Big-O Notation: O(1)
 * Adds x as the first item in the deque pointed to by dp
 */
void addFirst(DEQUE *dp, int x) {
    assert(dp != NULL);

    struct node *pAdd;
    pAdd = malloc(sizeof (struct node));
    assert(pAdd != NULL);

    pAdd->data = x;
    
    pAdd->used = 0;
    pAdd->time = 0;

    pAdd->prev = dp->dummy;
    pAdd->next = dp->dummy->next;

    dp->dummy->next->prev = pAdd;
    dp->dummy->next = pAdd;

    dp->count++;
}

/*
 * Big-O Notation: O(1)
 * Adds x as the last item in the deque pointed to by dp
 */
void addLast(DEQUE *dp, int x) {
    assert(dp != NULL);

    struct node *pAdd;
    pAdd = malloc(sizeof (struct node));
    assert(pAdd != NULL);

    pAdd->data = x;
    
    pAdd->used = 0;
    pAdd->time = 0;

    pAdd->next = dp->dummy;
    pAdd->prev = dp->dummy->prev;
    
    dp->dummy->prev->next = pAdd;
    dp->dummy->prev = pAdd;

    dp->count++;
}

/*
 * Big-O Notation: O(1)
 * Removes and returns the first item in the deque pointed to by dp; the deque must not be empty
 */
int removeFirst(DEQUE *dp) {
    assert(dp != NULL);

    int data;

    struct node *pDel = dp->dummy->next;
    struct node *tempNext = pDel->next;

    data = pDel->data;

    dp->dummy->next = tempNext;
    
    tempNext->prev = dp->dummy;
    tempNext->next = pDel->next->next;

    free(pDel);

    dp->count--;

    return data;
}

/*
 * Big-O Notation: O(1)
 * Removes and returns the last item in the deque pointed to by dp; the deque must not be empty
 */
int removeLast(DEQUE *dp) {
    assert(dp != NULL);

    int data;

    struct node *pDel = dp->dummy->prev;
    struct node *tempLast = pDel->prev;

    data = pDel->data;

    dp->dummy->prev = pDel->prev;
    
    tempLast->next = dp->dummy;
    dp->dummy->prev = tempLast;

    free(pDel);

    dp->count--;
    
    return data;
}

/*
 * Big-O Notation: O(1)
 * Returns, but does not remove, the first item in the deque pointed to by dp; the deque must not be empty
 */
int getFirst(DEQUE *dp) {
    assert(dp != NULL && dp->count != 0);

    return dp->dummy->next->data;
}

/*
 * Big-O Notation: O(1)
 * Returns, but does not remove, the last item in the deque pointed to by dp; the deque must not be empty
 */
int getLast(DEQUE *dp) {
    assert(dp != NULL && dp->count != 0);

    return dp->dummy->prev->data;
}

/*
 * Big-O Notation: O(n)
 * Returns and finds a node in the deque with value x
 */
NODE *findNode(DEQUE *dp, int x) {
    int found = 0;
    NODE *np = dp->dummy->next;
    
    while (np != dp->dummy) {
        if (np->data == x) {
            found = 1;
            break;
        }
        np = np->next;
    }
    
    if (found != 1)
        return NULL;
    return np;
}

/*
 * Big-O Notation: O(1)
 * Set time of node with value x in deque with value time
 */
void setTime(DEQUE *dp, int x, int time) {
    NODE *np = findNode(dp, x);
    np->time = time;
    np->used++;
}

/*
 * Big-O Notation: O(1)
 * Set time of last node in deque with value time
 */
void setLastTime(DEQUE *dp, int time) {
    assert(dp != NULL);
    
    dp->dummy->prev->time = time;
    dp->dummy->prev->used++;
}

/*
 * Big-O Notation: O(n)
 * Remove node in deque with lowest time
 */
void removeOldestTime(DEQUE *dp) {
    assert(dp != NULL && dp->count != 0);
    
    NODE *np = dp->dummy->next;
    NODE *least = np;
    
    while (np != dp->dummy) {
        if (np->time < least->time) {
            least = np;
        }
        np = np->next;
    }
    
    least->prev->next = least->next;
    least->next->prev = least->prev;
    free(least);
    dp->count--;
}

/*
 * Big-O Notation: O(n)
 * Remove node in deque with lowest used value
 */
void removeLeastUsed(DEQUE *dp) {
    assert(dp != NULL && dp->count != 0);
    
    NODE *np = dp->dummy->next;
    NODE *least = np;
    
    while (np != dp->dummy) {
        if (np->used < least->used) {
            least = np;
        } //break tie with older page
        else if (np ->used == least->used && np->time < least ->time) {
            least = np;
        }
        np = np->next;
    }
    
    least->prev->next = least->next;
    least->next->prev = least->prev;
    free(least);
    dp->count--;
}

/*
 * Big-O Notation: O(n)
 * Print each node in deque
 */
void printDeque(DEQUE *dp) {
    NODE* np = dp->dummy->next;
    
    while (np != dp->dummy) {
        printf("data:%d; time: %d; used: %d\n",np->data, np->time, np->used);
        np = np->next;
    }
    printf("------------------------------\n");
}
