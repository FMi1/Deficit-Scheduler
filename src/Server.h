//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is Turndistributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SERVER_H_
#define SERVER_H_

#include <omnetpp.h>
#include <queue>
#include "DSMessage.h"

using namespace omnetpp;

class Server : public cSimpleModule{

private:
    cMessage *pick_job;
    cMessage *send_job;
    std::deque<DSMessage*> _queue;
    double mean_vacation;
    double mean_serviceTime;
    bool in_vacation;
    unsigned int served_job;
    unsigned int turn_number;

    simtime_t _turn;
    simtime_t _deficit;
    simtime_t last_departure;

    simsignal_t response_time_signal;
    simsignal_t jobs_signal;
    simsignal_t waiting_time_signal;
    simsignal_t service_time_signal;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage* message);
    virtual void finish();




};

#endif /* SERVER_H_ */
