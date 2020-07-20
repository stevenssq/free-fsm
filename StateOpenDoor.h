#ifndef STATE_OPEN_DOOR
#define STATE_OPEN_DOOR

#include "State.h"

class StateOpenDoor : public State
{
public:
    StateOpenDoor(State *parent = 0);
    virtual ~StateOpenDoor();

    virtual void onEntry(std::string paraP);
    virtual void handleTimeout();
    virtual void onExit();

};

#endif
