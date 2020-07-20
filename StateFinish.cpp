#include <unistd.h>
#include "StateFinish.h"

StateFinish::StateFinish(State *parent) :
    State(parent)
{

}

StateFinish:: ~StateFinish()
{

}

void StateFinish::onEntry(std::string paraP)
{
    dzlog_info("StateFinish::onEntry()");
    parentM->postEvent("get job");
    sleep(2);
}

void StateFinish::handleTimeout()
{
    dzlog_info("StateFinish::handleTimeout()");
}

void StateFinish::onExit()
{
    dzlog_info("StateFinish::onExit()");
}
