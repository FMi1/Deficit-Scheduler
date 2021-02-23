#include "DSMessage.h"

DSMessage::DSMessage(int _id,simtime_t service_time ) {
    this->_id=_id;
    this->service_time=service_time;
    this->_times.vacation_time=0;
    this->support_vacation=0;
    this->_times.creation_time = simTime();
    this->head=false;
}

int DSMessage::getId(){
    return this->_id;
}

simtime_t DSMessage::getServiceTime(){
    return this->service_time;
}
simtime_t DSMessage::getCreationTime(){
    return this->_times.creation_time;
}
simtime_t DSMessage::getArrivalTime(){
    return this->_times.arrival_time;
}
simtime_t DSMessage::getDepartureTime(){
    return this->_times.departure_time;
}
simtime_t DSMessage::getVacationTime(){
    return this->_times.vacation_time;
}

void DSMessage::setArrivalTime(simtime_t arrival_time){
    this->_times.arrival_time=arrival_time;
}

void DSMessage::setDepartureTime(simtime_t departure_time){
    this->_times.departure_time=departure_time;
}

void DSMessage::addVacationTime(simtime_t vacation_time){
    this->_times.vacation_time+=vacation_time;
}

void DSMessage::addSupportVacation(simtime_t tempo){
    this->support_vacation=tempo;
}

simtime_t DSMessage::getSupportVacation(){
    return this->support_vacation;
}

void DSMessage::setHead(bool head){
    this->head=head;
}
bool DSMessage::getHead(){
    return this->head;
}
