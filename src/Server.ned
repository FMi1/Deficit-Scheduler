package projectpecsn;

//
// TODO auto-generated type
//
simple Server
{
    parameters:
        
        @signal[responseTime](type=long);
   	    @statistic[responseTimeStat](source="responseTime"; record=mean;);
   	      	    
   	    @signal[Jobs](type=long);
   	    @statistic[JobsStat](source="Jobs"; record=mean;);
   	      	    
   	    @signal[waitingTime](type=long);
   	    @statistic[waitingTimeStats](source="waitingTime"; record=mean;);
   	    
   	    @signal[serviceTime](type=long);
   	    @statistic[serviceTimeStat](source="serviceTime"; record=vector;);
    gates:
        input in;
}
