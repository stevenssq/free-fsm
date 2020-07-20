#include <unistd.h>
#include "StateBeginCharge.h"

StateBeginCharge::StateBeginCharge(State *parent) :
    State(parent)
{

}

StateBeginCharge:: ~StateBeginCharge()
{

}

void StateBeginCharge::onEntry(std::string paraP)
{
    dzlog_info("StateBeginCharge::onEntry()");
    parentM->postEvent("begin charge");
    sleep(2);
}

void StateBeginCharge::handleTimeout()
{
    dzlog_info("StateBeginCharge::handleTimeout()");
    parentM->postEvent("open door");
}

void StateBeginCharge::onExit()
{
    dzlog_info("StateBeginCharge::onExit()");
}
