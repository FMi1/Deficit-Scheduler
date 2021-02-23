#ifndef JOBPRODUCER_H_
#define JOBPRODUCER_H_

#include "DSMessage.h"
#include <omnetpp.h>

using namespace omnetpp;

class JobProducer : public cSimpleModule{
private:
    DSMessage* _message;
    cMessage* _beep;
    int id_counter;
    double mean_interarrival;
    double mean_vacation;
    double mean_serviceTime;
    double q;
    double ro;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage * _message);
    virtual void finish();
    simtime_t createServiceTime();
};

#endif /* JOBPRODUCER_H_ */
