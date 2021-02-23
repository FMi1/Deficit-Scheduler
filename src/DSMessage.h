#ifndef DSMESSAGE_H_
#define DSMESSAGE_H_

#include <omnetpp.h>
#include <math.h>

using namespace omnetpp;

class DSMessage : public cMessage {
private:
    int _id;
    simtime_t service_time;
    simtime_t support_vacation;
    bool head;

    struct{
        simtime_t creation_time;
        simtime_t arrival_time;
        simtime_t departure_time;
        simtime_t vacation_time;
        } _times;
public:
    DSMessage(int _id,simtime_t service_time);
    int getId();
    simtime_t getServiceTime();
    simtime_t getCreationTime();
    simtime_t getArrivalTime();
    simtime_t getDepartureTime();
    simtime_t getVacationTime();
    simtime_t getSupportVacation();

    void setArrivalTime(simtime_t arrival_time);
    void setDepartureTime(simtime_t departure_time);
    void addVacationTime(simtime_t vacation_time);
    void addSupportVacation(simtime_t tempo);
    void setHead(bool head);
    bool getHead();
};

#endif /* DSMESSAGE_H_ */
