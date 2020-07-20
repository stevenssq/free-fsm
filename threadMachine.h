#ifndef THREAD_MACHINE_H
#define THREAD_MACHINE_H

#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

void createMachineThread();

enum{
    START_MACHINE = 5,
    STOP_MACHINE = 6,
    BEGIN_WORK = 7,
    BEGIN_CHARGE = 8,
};

#ifdef __cplusplus
}
#endif

#endif
