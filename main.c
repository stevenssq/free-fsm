#include <unistd.h>
#include <sys/stat.h>
#include "threadMachine.h"
#include "signalbase/signalbase.h"
#include "zlog.h"

int initZlog()
{
    if (-1 == access("/home/fsmlog", F_OK))
    {
        mkdir("/home/fsmlog", 0777);
    }

    if (dzlog_init("zlog.conf", "fsm") != 0)
    {
        printf("init zlog failed\n");
        return -1;
    }

    return 0;
}


int main()
{
    initZlog();
    createMachineThread();
    sleep(2);
    sendSignalToThread(BEGIN_CHARGE, "stateMachine");
    sleep(1);
    sendSignalToThread(STOP_MACHINE, "stateMachine");
    sleep(1);
    sendSignalToThread(BEGIN_WORK, "stateMachine");
    sendSignalToThread(START_MACHINE, "stateMachine");
    sendSignalToThread(STOP_MACHINE, "stateMachine");
    sendSignalToThread(START_MACHINE, "stateMachine");


    while(1)
    {
        usleep(100);
    }
}
