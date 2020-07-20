#ifndef STATE_GOTO_POINT
#define STATE_GOTO_POINT

#include "State.h"

class StateGotoPoint : public State
{
public:
    StateGotoPoint(State *parent = 0);
    virtual ~StateGotoPoint();

    virtual void onEntry(std::string paraP);
    virtual void handleTimeout();
    virtual void onExit();

};

#endif
