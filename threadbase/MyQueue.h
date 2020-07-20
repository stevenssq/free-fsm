#include "stdbool.h"

#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#define QUEUE_SIZE  100
#define ARRAY_SIZE   (QUEUE_SIZE + 1)

typedef struct tThreadQueue
{
    int queue[ARRAY_SIZE];
    int front;
    int rear;
}tThreadQueue;

bool insert(int value, tThreadQueue *pQueue);
int popFront(tThreadQueue *pQueue);
int front(tThreadQueue *pQueue);
bool isEmpty(tThreadQueue *pQueue);
bool isFull(tThreadQueue *pQueue);

#ifdef __cplusplus
}
#endif

#endif
