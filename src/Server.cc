#include "Server.h"

Define_Module(Server);

void Server::initialize(){
    served_job=0;
    in_vacation=true;
    pick_job = new cMessage("pick");
    send_job=new cMessage("send");
    //getting system factors
    mean_vacation=getParentModule()->par("Vacation").doubleValue();
    mean_serviceTime=getParentModule()->par("ServiceTime").doubleValue();
    _turn=getParentModule()->par("TurnServiceRatio").doubleValue()*mean_serviceTime;
    //initializing deficit value with Q value
    _deficit=_turn;
    //initializing the turn counter to 0
    turn_number=0;
    last_departure=0;
    //registering signals
    response_time_signal = registerSignal("responseTime");
    jobs_signal =registerSignal("Jobs");
    waiting_time_signal=registerSignal("waitingTime");
    service_time_signal=registerSignal("serviceTime");
    //starting the server
    scheduleAt(simTime(), pick_job);


}

void Server::handleMessage(cMessage* message){
    simtime_t vacation;
    //pick event, the server comes back from vacation and tries to pick a new job from the queue
    if(strcmp(message->getName(),"pick")==0){
        in_vacation=false;
        //check if queue is empty
        if(_queue.empty()){
            //if the queue is empty the server takes a new vacation
            _deficit=_turn;
            //computing the new vacation value
            if(getParentModule()->par("exponentialDistribution").boolValue())
                vacation = exponential(mean_vacation,2);
            else
                vacation = mean_vacation;
            //setting the state of the system to "in vacation"
            in_vacation=true;
            turn_number++;
            scheduleAt(simTime() + vacation, pick_job);
        }

        else{
            DSMessage* serving=_queue.front();
            //if the job wasn't the head of the queue according the model
            //it goes under service even if it will not be server in the current turn
            if(serving->getHead()==false){
                //sending the waiting time
                serving->setHead(true);
                emit(waiting_time_signal,simTime()-serving->getArrivalTime());
            }
            //if at the job's arrival, the server was in vacation and queue is empty according to the model
            //the job is immediately considered in service. In order to create its ST' we need to add this vacation time
            //to its ST
            if(serving->getSupportVacation()!=0){
                serving->addVacationTime(simTime()-serving->getSupportVacation());
                serving->addSupportVacation(0);
            }
            //if the queue is not empty the server checks if the ST doesn't exceed the residual of the turn time
            if(serving->getServiceTime()<=_deficit){
                emit(jobs_signal,_queue.size()-1);
                scheduleAt(simTime()+serving->getServiceTime(),send_job);
            }
            else{
                //if the server cannot serve the job in this turn he takes a new vacation
                //adding the deficit to the next turn time
                if(getParentModule()->par("exponentialDistribution").boolValue())
                    vacation = exponential(mean_vacation,2);
                else
                    vacation = mean_vacation;
                serving->addVacationTime(vacation);
                _deficit+=_turn;
                in_vacation=true;
                turn_number++;
                scheduleAt(simTime() + vacation, pick_job);
            }
       }
    }
    else if(strcmp(message->getName(),"send")==0){
        //if the message is the send one the server has completed the service of the job
        DSMessage* serving=_queue.front();
        _queue.pop_front();
        serving->setDepartureTime(simTime());
        _deficit-=serving->getServiceTime();
        last_departure=simTime();
        served_job++;
        emit(response_time_signal,(serving->getDepartureTime()-serving->getArrivalTime()));
        emit(service_time_signal,serving->getVacationTime()+serving->getServiceTime());
        delete serving;
        scheduleAt(simTime(),pick_job);
    }
    else{
        //the last type of message is the receiving one from the JobProducer
        DSMessage *job = check_and_cast<DSMessage*>(message);
        job->setArrivalTime(simTime());
        //we need to perform an additional check in order to maintain the system consistent
        //with the model
        if(in_vacation && _queue.empty()){
               job->setHead(true);
               job->addSupportVacation(SimTime());
               emit(waiting_time_signal,0.0);
        }
        emit(jobs_signal,_queue.size());
        _queue.push_back(job);
   }
}

void Server::finish(){
    EV<<"Serverd Job= "<<served_job<<endl;
    EV<<"Last Departure= "<<last_departure<<endl;
    EV<<"Jobs in queue= "<<_queue.size()<<endl;
    EV<<"Turn number= "<<turn_number<<endl;

    cancelEvent(pick_job);
    cancelEvent(send_job);
    cancelAndDelete(pick_job);
    cancelAndDelete(send_job);

    while(!_queue.empty()){
        cancelAndDelete(_queue.front());
        _queue.pop_front();
    }


}
