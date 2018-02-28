# ifndef DEQUE_H
# define DEQUE_H

#include "deque.c"

extern DEQUE *createDeque(void);

extern void destroyDeque(DEQUE *dp);

extern int numItems(DEQUE *dp);

extern void addFirst(DEQUE *dp, int x);

extern void addLast(DEQUE *dp, int x);

extern int removeFirst(DEQUE *dp);

extern int removeLast(DEQUE *dp);

extern int getFirst(DEQUE *dp);

extern int getLast(DEQUE *dp);

extern NODE *findNode(DEQUE *dp, int x);

extern void setTime(DEQUE *dp, int x, int time);

extern void setLastTime(DEQUE *dp, int time);

extern void removeOldestTime(DEQUE *dp);

extern void removeLeastUsed(DEQUE *dp);

extern void printDeque(DEQUE *dp);

# endif /* DEQUE_H */

