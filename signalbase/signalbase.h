#ifndef SIGNAL_BASE
#define SIGNAL_BASE

#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

int sendSignalToThread(int signum, const char *threadName);
int getThreadSignal(const char *threadName);

#ifdef __cplusplus
}
#endif

#endif
