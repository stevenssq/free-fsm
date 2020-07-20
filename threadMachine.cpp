#include <unistd.h>
#include <memory.h>
#include <iostream>
#include "threadMachine.h"
#include "StateGetJob.h"
#include "StateGotoPoint.h"
#include "StateBeginCharge.h"
#include "StateOpenDoor.h"
#include "StateCloseDoor.h"
#include "StateFinish.h"
#include "StateFinal.h"
#include "StateMachine.h"
#include "threadbase/threadbase.h"
#include "signalbase/signalbase.h"
#include "threadbase/MyQueue.h"

StateMachine *pStateMachine = new StateMachine();

static void *ThreadMachine(void *pvPara)
{
    pvPara = pvPara;

    State *pWorkState = new State(pStateMachine);
    State *pChargeState = new State(pStateMachine);
    StateFinal *pStateFinal = new StateFinal(pStateMachine);

    StateGetJob *pStateGetJob = new StateGetJob(pWorkState);
    StateGotoPoint *pStateGotoPoint = new StateGotoPoint(pWorkState);
    StateFinish *pStateFinish = new StateFinish(pWorkState);

    StateBeginCharge *pStateBeginCharge = new StateBeginCharge(pChargeState);
    StateOpenDoor *pStateOpenDoor = new StateOpenDoor(pChargeState);
    StateCloseDoor *pCloseDoor = new StateCloseDoor(pChargeState);

    pWorkState->addState("get job", pStateGetJob);
    pWorkState->addState("goto point", pStateGotoPoint);
    pWorkState->addState("finished", pStateFinish);
    pWorkState->setInitState(pStateGetJob);

    pChargeState->addState("begin charge", pStateBeginCharge);
    pChargeState->addState("open door", pStateOpenDoor);
    pChargeState->addState("close door", pCloseDoor);
    pChargeState->setInitState(pStateBeginCharge);

    pStateMachine->addState("work state", pWorkState);
    pStateMachine->addState("charge state", pChargeState);
    pStateMachine->addFinalState(pStateFinal);
    pStateMachine->setInitState(pWorkState);

    pStateMachine->start();

    int signo = 0;

    while(1)
    {
        signo = getThreadSignal("stateMachine");
        if (-255 == signo)
        {
            usleep(10);
            continue;
        }

        switch (signo)
        {
            case START_MACHINE:
                dzlog_info("receive signal start machine,signum:%d", signo);
                pStateMachine->start();
                break;
            case STOP_MACHINE:
                dzlog_info("receive signal stop machine,signum:%d", signo);
                pStateMachine->stop();
                break;
            case BEGIN_WORK:
                dzlog_info("receive signal begin Work, signum:%d", signo);
                pStateMachine->transferState("work state");
                break;
            case BEGIN_CHARGE:
                dzlog_info("receive signal begin charge, signum:%d", signo);
                pStateMachine->transferState("charge state");
                sleep(10);
                break;
            default:
                dzlog_info("unexpected signal:%d", signo);
        }
    }

    return NULL;
}

void createMachineThread()
{
    ThreadCreateParaDef tThreadCreatePara;
    memset(&tThreadCreatePara, 0, sizeof(ThreadCreateParaDef));
    tThreadCreatePara.ps8Name = (char *)"stateMachine";
    tThreadCreatePara.pvFuncPara = NULL;
    tThreadCreatePara.EntryFuncPt = ThreadMachine;
    createThread(&tThreadCreatePara);
}
