#ifndef STATE_FINAL
#define STATE_FINAL

#include "State.h"

class StateFinal : public State
{
public:
    StateFinal(State *parent = 0);
    virtual ~StateFinal();

    virtual void onEntry(std::string paraP);
    virtual void onExit();

};


#endif
