#include "MyQueue.h"

bool insert(int value, tThreadQueue *pQueue)
{
    if (isFull(pQueue))
    {
        return false;
    }

    pQueue->rear = (pQueue->rear + 1) % ARRAY_SIZE;
    pQueue->queue[pQueue->rear] = value;

    return true;
}

int popFront(tThreadQueue *pQueue)
{
    if (isEmpty(pQueue))
    {
        return -255;
    }

    int tempValue = pQueue->queue[pQueue->front];
    pQueue->front = (pQueue->front + 1) % ARRAY_SIZE;

    return tempValue;
}

int front(tThreadQueue *pQueue)
{
    if (isEmpty(pQueue))
    {
        return -255;
    }

    return pQueue->queue[pQueue->front];
}

bool isEmpty(tThreadQueue *pQueue)
{
    return (pQueue->rear + 1) % ARRAY_SIZE == pQueue->front;
}

bool isFull(tThreadQueue *pQueue)
{
    return (pQueue->rear + 2) % ARRAY_SIZE == pQueue->front;
}
