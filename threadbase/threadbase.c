#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/prctl.h>
#include "threadbase.h"

LIST_HEAD(threadListHead);

static void *threadInterface(void *pvPara)
{
    ThreadCreateParaDef *ptThreadCreatePara = (ThreadCreateParaDef *)pvPara;
    void *pvFuncPara = ptThreadCreatePara->pvFuncPara;

    prctl(PR_SET_NAME, ptThreadCreatePara->ps8Name);
	
    if(NULL != pvPara)
    {
        free(pvPara);
    }

    (*ptThreadCreatePara->EntryFuncPt)(pvFuncPara);

    return NULL;
}

int createThread(ThreadCreateParaDef *ptThreadCreatePara)
{
    pthread_t threadID;
    pthread_attr_t tThreadAttr;
    ThreadCreateParaDef *pthreadPara = NULL;
    tThreadInfo *newThreadInfo = NULL;

    pthreadPara = (ThreadCreateParaDef *)malloc(sizeof(ThreadCreateParaDef));
    memcpy(pthreadPara, ptThreadCreatePara, sizeof(ThreadCreateParaDef));

    pthread_attr_init(&tThreadAttr);

    if(pthread_create(&threadID, &tThreadAttr, threadInterface, pthreadPara) != 0)
    {
        printf("Thread startup error, thread name:%s\n", ptThreadCreatePara->ps8Name);
        if (pthreadPara != NULL)
        {
            free(pthreadPara);
        }
        return -1;
    }

    newThreadInfo = (tThreadInfo *)malloc(sizeof(tThreadInfo));
    memset(newThreadInfo, 0, sizeof(tThreadInfo));
    newThreadInfo->pid = threadID;
    strncpy(newThreadInfo->threadName, ptThreadCreatePara->ps8Name, MAX_NAME_LEN - 1);
    newThreadInfo->msgList.front = 1;
    newThreadInfo->msgList.rear = 0;
    pthread_mutex_init(&newThreadInfo->threadQueueMutex, NULL);
    list_add_tail(&newThreadInfo->list, &threadListHead);

    return 0;
}
