/*
 * File:	deque.h
 *
 * Description:	This file contains the public function declarations for a
 *		deque abstract data type for integers.  A deque is a
 *		doubly-ended queue, in which items can only be added to or
 *		removed from the front or rear of the list.
 */

# ifndef DEQUE_H
# define DEQUE_H

#include "deque.c"

typedef struct deque DEQUE;
typedef struct node NODE;

extern DEQUE *createDeque(void);

extern void destroyDeque(DEQUE *dp);

extern int numItems(DEQUE *dp);

extern void addFirst(DEQUE *dp, int x);

extern void addLast(DEQUE *dp, int x);

extern int removeFirst(DEQUE *dp);

extern int removeLast(DEQUE *dp);

extern int getFirst(DEQUE *dp);

extern int getFirstRef(DEQUE *dp);

extern int getLast(DEQUE *dp);

extern NODE* findNode(DEQUE *dp, int x);

extern void moveToFront(DEQUE *dp, int x);

extern void setTime(DEQUE *dp, int x, int time);

extern void setLastTime(DEQUE *dp, int time);

extern void removeOldestTime(DEQUE *dp);

extern void removeLeastUsed(DEQUE *dp);

extern void removeRandom(DEQUE *dp);

extern void printDeque(DEQUE *dp);

# endif /* DEQUE_H */
