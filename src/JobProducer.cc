#include "JobProducer.h"

Define_Module(JobProducer);

void JobProducer:: initialize(){
    id_counter = 0;
    //new self-message to start the JP process
    _beep = new cMessage();
    //getting all the system factors
    mean_vacation=getParentModule()->par("Vacation").doubleValue();
    mean_serviceTime=getParentModule()->par("ServiceTime").doubleValue();
    q=getParentModule()->par("TurnServiceRatio").doubleValue()*mean_serviceTime;
    mean_interarrival=mean_serviceTime*(mean_vacation+q)/q;
    ro=getParentModule()->par("ro").doubleValue();
    if(getParentModule()->par("exponentialDistribution").boolValue())
        mean_interarrival=mean_interarrival/ro;
    //start
    scheduleAt(simTime(), this->_beep);
}

simtime_t JobProducer:: createServiceTime(){
    if(getParentModule()->par("exponentialDistribution").boolValue())
         return exponential(mean_serviceTime,0);
    return mean_serviceTime;
}

void JobProducer:: handleMessage(cMessage* _message){
    this->_message = new DSMessage(id_counter,createServiceTime());
    id_counter++;
    send(this->_message,"out");
    simtime_t time;
    if(getParentModule()->par("exponentialDistribution").boolValue()){
        time = exponential((mean_interarrival),1);
    }
    else
        time = mean_interarrival;
    scheduleAt(simTime() + time, this->_beep);
}

void JobProducer::finish(){
    cancelEvent(this->_beep);
    cancelAndDelete(this->_beep);
}
