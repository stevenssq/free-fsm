#include "signalbase.h"
#include <string.h>
#include "threadbase/threadbase.h"
#include "threadbase/MyQueue.h"

extern struct list_head threadListHead;
int sendSignalToThread(int signum, const char *threadName)
{
    struct list_head *node;
    tThreadInfo *pthreadInfo;
    __list_for_each(node, &threadListHead)
    {
        pthreadInfo = list_entry(node, tThreadInfo, list);
        if (!strncmp(pthreadInfo->threadName, threadName, MAX_NAME_LEN))
        {
            pthread_mutex_lock(&pthreadInfo->threadQueueMutex);
            insert(signum, &pthreadInfo->msgList);
            pthread_mutex_unlock(&pthreadInfo->threadQueueMutex);

            return 0;
        }
    }

    return -1;
}

int getThreadSignal(const char *threadName)
{
    struct list_head *node;
    tThreadInfo *pthreadInfo;
    int signo = -255;
    __list_for_each(node, &threadListHead)
    {
        pthreadInfo = list_entry(node, tThreadInfo, list);
        if (!strncmp(pthreadInfo->threadName, threadName, MAX_NAME_LEN))
        {
            pthread_mutex_lock(&pthreadInfo->threadQueueMutex);
            signo =  popFront(&pthreadInfo->msgList);
            pthread_mutex_unlock(&pthreadInfo->threadQueueMutex);

        }
    }

    return signo;
}
