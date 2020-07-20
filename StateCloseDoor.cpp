#include <unistd.h>
#include "StateCloseDoor.h"
#include "threadMachine.h"
#include "signalbase/signalbase.h"

StateCloseDoor::StateCloseDoor(State *parent) :
    State(parent)
{

}

StateCloseDoor:: ~StateCloseDoor()
{

}

void StateCloseDoor::onEntry(std::string paraP)
{
    dzlog_info("StateCloseDoor::onEntry()");
    if (!paraP.empty())
    {
        std::cout<<"str:"<<paraP<<std::endl;
    }

    parentM->postEvent("close door");
    sleep(2);
}

void StateCloseDoor::handleTimeout()
{
    dzlog_info("StateCloseDoor::handleTimeout()");
    sendSignalToThread(BEGIN_WORK, "stateMachine");
}

void StateCloseDoor::onExit()
{
    dzlog_info("StateCloseDoor::onExit()");
}
