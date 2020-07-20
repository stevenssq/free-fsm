#ifndef STATE_CLOSE_DOOR
#define STATE_CLOSE_DOOR

#include "State.h"

class StateCloseDoor : public State
{
public:
    StateCloseDoor(State *parent = 0);
    virtual ~StateCloseDoor();

    virtual void onEntry(std::string paraP);
    virtual void handleTimeout();
    virtual void onExit();

};


#endif
