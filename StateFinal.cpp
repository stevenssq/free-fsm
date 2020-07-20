#include <unistd.h>
#include "StateFinal.h"

StateFinal::StateFinal(State *parent) :
    State(parent)
{

}

StateFinal:: ~StateFinal()
{

}

void StateFinal::onEntry(std::string paraP)
{
    dzlog_info("StateFinal::onEntry()");
    //sleep(2);
}

void StateFinal::onExit()
{
    dzlog_info("StateFinal::onExit()");
}
