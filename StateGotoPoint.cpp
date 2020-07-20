#include <unistd.h>
#include "StateGotoPoint.h"

StateGotoPoint::StateGotoPoint(State *parent) :
    State(parent)
{

}

StateGotoPoint:: ~StateGotoPoint()
{

}

void StateGotoPoint::onEntry(std::string paraP)
{
    dzlog_info("StateGotoPoint::onEntry()");
    parentM->postEvent("finished");
    sleep(1);
}

void StateGotoPoint::handleTimeout()
{
    dzlog_info("StateGotoPoint::handleTimeout()");
}

void StateGotoPoint::onExit()
{
    dzlog_info("StateGotoPoint::onExit()");
}
