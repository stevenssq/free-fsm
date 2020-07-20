#include <unistd.h>
#include "StateGetJob.h"

StateGetJob::StateGetJob(State *parent) :
    State(parent)
{

}

StateGetJob:: ~StateGetJob()
{

}

void StateGetJob::onEntry(std::string paraP)
{
    dzlog_info("StateGetJob::onEntry()");
    parentM->postEvent("get job");
    sleep(1);
}

void StateGetJob::handleTimeout()
{
    dzlog_info("StateGetJob::handleTimeout()");
    parentM->postEvent("goto point");
}

void StateGetJob::onExit()
{
    dzlog_info("StateGetJob::onExit()");
}
