#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include <map>
#include "zlog.h"

typedef struct
{
    std::string nextState;
    std::string para;
}S_EVENT;

class State
{
public:
    State(State *parent = 0);
    virtual ~State();

public:
    virtual void onEntry(std::string paraP);
    virtual void onExit();
    virtual void handleTimeout();
    void postEvent(std::string eventP, std::string paraP = "");
    void stateEntry();
    void stateExit();
    void executeState();
    void setInitState(State *pInitStateP);
    void addState(std::string transEvent, State *nextState);

private:
    S_EVENT getNextEvent();
    void stateInit();

protected:
    enum
    {
        DELAY_2SEC = 2 * 1000,
        DELAY_3SEC = 3 * 1000,
        DELAY_30SEC = 30 * 1000,
    };

protected:
    State *parentM;
    State *initStateM;
    State *currentStateM;
    State *lastStateM;
    S_EVENT currentEventM;
    S_EVENT lastEventM;
    std::list<S_EVENT> eventListM;
    std::map <std::string,  State*> stateMapM;
};

#endif
