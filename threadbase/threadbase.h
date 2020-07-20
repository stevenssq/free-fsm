#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include <pthread.h>
#include "list.h"
#include "MyQueue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NAME_LEN 32

typedef struct ThreadCreateParaDef
{
    char *ps8Name;//  线程名称
    void *(*EntryFuncPt)(void *);//  线程入口函数
    void *pvFuncPara;//  线程参数
}ThreadCreateParaDef;

typedef struct tThreadInfo
{
    struct list_head list;
    pthread_t pid;
    char threadName[MAX_NAME_LEN];
    tThreadQueue msgList;
    pthread_mutex_t threadQueueMutex;
}tThreadInfo;

int createThread(ThreadCreateParaDef *ptThreadCreatePara);

#ifdef __cplusplus
}
#endif

#endif
