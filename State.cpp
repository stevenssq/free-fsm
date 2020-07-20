#include "State.h"
#include "zlog.h"
#include <unistd.h>

State::State(State *parent) :
    parentM(parent),
    initStateM(NULL)
{
    stateInit();
}

State::~State()
{
    stateMapM.clear();
}

void State::stateInit()
{
    currentStateM = NULL;
    lastStateM = NULL;
    currentEventM = {"", ""};
    lastEventM = {"", ""};
    eventListM.clear();
}

void State::onEntry(std::string paraP)
{
    paraP = paraP;
}

void State::handleTimeout()
{

}

void State::onExit()
{

}

void State::stateEntry()
{
    stateInit();
    currentStateM = initStateM;
}

void State::stateExit()
{
    if (lastStateM != NULL)
    {
        lastStateM->onExit();
    }
}

void State::setInitState(State *pInitStateP)
{
    initStateM = pInitStateP;
}

void State::executeState()
{
    if (NULL == currentStateM)
    {
        dzlog_info("State::null point currentStateM");
        sleep(1);
        return;
    }

    if (lastStateM != currentStateM && lastStateM != NULL)
    {
        lastStateM->onExit();
    }

    if (lastStateM == currentStateM)
    {
        currentStateM->handleTimeout();
    }
    else
    {
        currentStateM->onEntry(currentEventM.para);
    }

    lastStateM = currentStateM;
    lastEventM = currentEventM;

    S_EVENT event = getNextEvent();
    std::map<std::string,  State*>::iterator iter;
    iter = stateMapM.find(event.nextState);
    if(iter != stateMapM.end())
    {
        currentStateM = iter->second;
        currentEventM = event;
    }
    else
    {
        currentStateM = NULL;
        usleep(1000);
    }
}

void State::addState(std::string transEvent, State *nextState)
{
    stateMapM.insert(make_pair(transEvent, nextState));
}

void State::postEvent(std::string eventP, std::string paraP)
{
    S_EVENT event = {eventP, paraP};
    eventListM.push_back(event);
}

S_EVENT State::getNextEvent()
{
    S_EVENT event = {"NULL event", ""};

    if (eventListM.empty())
    {
        return event;
    }

    while (eventListM.size())
    {
        event = eventListM.front();
        eventListM.pop_front();
    }

    return event;
}
