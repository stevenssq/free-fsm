#ifndef STATE_BEGIN_CHARGE
#define STATE_BEGIN_CHARGE

#include "State.h"

class StateBeginCharge : public State
{
public:
    StateBeginCharge(State *parent = 0);
    virtual ~StateBeginCharge();

    virtual void onEntry(std::string paraP);
    virtual void handleTimeout();
    virtual void onExit();

};

#endif
