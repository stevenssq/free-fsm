#include <iostream>
#include <unistd.h>
#include "StateMachine.h"
#include "memory.h"
#include "threadbase/threadbase.h"

StateMachine::StateMachine():
    finalStateM(NULL),
    machineStateM(INIT),
    threadHasCreated(false)
{
    pthread_mutex_init(&transVecMutexM, NULL);
}

StateMachine::~StateMachine()
{

}

void StateMachine::addFinalState(State *pFinalStateP)
{
    finalStateM = pFinalStateP;
}

void StateMachine::setTransEvent(S_TransEvent transEventP)
{
    pthread_mutex_lock(&transVecMutexM);
    transVecM.push_back(transEventP);
    pthread_mutex_unlock(&transVecMutexM);
}

S_TransEvent StateMachine::getTransEvent()
{
    pthread_mutex_lock(&transVecMutexM);
    S_TransEvent transEvent = transVecM.front();
    transVecM.erase(transVecM.begin());
    pthread_mutex_unlock(&transVecMutexM);

    return transEvent;
}

void StateMachine::executeState()
{
    if (NULL == currentStateM)
    {
        dzlog_info("StateMachine::null point currentStateM");
		sleep(1);
        return;
    }

    if (currentStateM != lastStateM)
    {
        if (lastStateM != NULL)
        {
            if (lastStateM == finalStateM)
            {
                lastStateM->onExit();
            }
            else
            {
                lastStateM->stateExit();
            }
        }
        lastStateM = currentStateM;
    }

    currentStateM->executeState();
}

void StateMachine::transferState(std::string transStateP)
{
    std::map<std::string,  State*>::iterator iter;
    iter = stateMapM.find(transStateP);
    if(iter != stateMapM.end())
    {
        S_TransEvent transEvent = {"transfer", iter->second};
        setTransEvent(transEvent);
    }
    else
    {
        S_TransEvent transEvent = {"transfer", NULL};
        setTransEvent(transEvent);
    }
}

void StateMachine::executeFinalState()
{
    if (finalStateM != NULL)
    {
        finalStateM->onEntry("");
        lastStateM = finalStateM;
    }
}

int StateMachine::getMachineState()
{
    return machineStateM;
}

void StateMachine::setMachineState(int stateP)
{
    machineStateM = stateP;
}

void StateMachine::transferOperate()
{
    if (transVecM.empty())
    {
        return;
    }

    S_TransEvent transEvent = getTransEvent();

    dzlog_info("cmd:%s!!!!!!", transEvent.cmd.c_str());
    if (transEvent.cmd == "start")
    {
        if (RUNNING == getMachineState())
        {
            dzlog_info("machine already runing, ignore!");
            return;
        }

        currentStateM = initStateM;
        if (currentStateM != NULL)
        {
            currentStateM->stateEntry();
        }
        setMachineState(RUNNING);
    }
    else if (transEvent.cmd == "stop")
    {
        if (STOPPED == getMachineState())
        {
            dzlog_info("machine already stopped, ignore!");
            return;
        }

        if (lastStateM != NULL)
        {
            lastStateM->stateExit();
        }
        lastStateM = NULL;
        executeFinalState();
        setMachineState(STOPPED);
    }
    else
    {
        if (STOPPED == getMachineState())
        {
            dzlog_info("state machine stopped, ignore transfer!");
            return;
        }

        if (transEvent.nextState == currentStateM)
        {
            dzlog_info("same state, ignore!");
        }
        else
        {
            lastStateM = currentStateM;
            currentStateM = transEvent.nextState;
            if (currentStateM != NULL)
            {
                currentStateM->stateEntry();
            }
        }
    }
}

void StateMachine::runningMachine()
{
    while (true)
    {
        usleep(10);
        transferOperate();

        switch(machineStateM)
        {
            case RUNNING:
                executeState();
                break;
              case STOPPED:
                usleep(100);
                break;
            default:
                break;
        }
    }
}

void StateMachine::start()
{
    dzlog_info("start machine...");

    S_TransEvent transEvent = {"start", NULL};
    setTransEvent(transEvent);

    if(false == threadHasCreated)
    {
        ThreadCreateParaDef tThreadCreatePara;
        memset(&tThreadCreatePara, 0, sizeof(ThreadCreateParaDef));
        tThreadCreatePara.ps8Name = (char *)"MachineInternal";
        tThreadCreatePara.pvFuncPara = (void *)this;
        tThreadCreatePara.EntryFuncPt = StateMachine::runningMachine_pthread;
        if (createThread(&tThreadCreatePara) != 0)
        {
            dzlog_info("can not create thread");
        }

        threadHasCreated = true;
    }
}

void StateMachine::stop()
{
    dzlog_info("stop machine...");

    S_TransEvent transEvent = {"stop", NULL};
    setTransEvent(transEvent);
}

void * StateMachine::runningMachine_pthread(void * __this)
{
    StateMachine * _this = (StateMachine *)__this;
    _this->runningMachine();

    return _this;
}
