#include <unistd.h>
#include <string.h>
#include "StateOpenDoor.h"

StateOpenDoor::StateOpenDoor(State *parent) :
    State(parent)
{

}

StateOpenDoor:: ~StateOpenDoor()
{

}

void StateOpenDoor::onEntry(std::string paraP)
{
    dzlog_info("StateOpenDoor::onEntry()");
    parentM->postEvent("open door");
    sleep(2);
}

void StateOpenDoor::handleTimeout()
{
    dzlog_info("StateOpenDoor::handleTimeout()");
    parentM->postEvent("close door", "hello");
}

void StateOpenDoor::onExit()
{
    dzlog_info("StateOpenDoor::onExit()");
}
