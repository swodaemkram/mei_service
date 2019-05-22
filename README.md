# mei_service
A stand alone service for the MEI validator 

This will be a stand alone service for the MEI validator that will take commands from a "connector"
application. This service will be a micro service and will offer an API and will communicate through a "connector" 
the "connector" will be a translating application that will take the single API provided by the MEI service and 
broaden the scope of the API to allow access to various disparate architectures.
For example a command line connector or a domain socket connector or a REST tcp/ip connector.
 This should give us unprecedented flexibility.
 
 The service will provide the following
 ------------------------------------------------------------------------------------------------
 COMMANDS:
 reset,
 verify,
 stack,
 idle,
 appver,
 bootver,
 model,
 serial,
 varname,
 
 -------------------------------------------------------------------------------------------------
 status|-----REPLYS
                |_busy
                |_stacking
                |_idling
                |_accepting
                |_returning
                |_escrowed
                |_drawing_in
                |_power_up
                |_processing
                |_stacked
                |_failure
                |_cassett_removed
                |_jamed
                |_full
                |_rejected
                |_cheated
                |_returned
                
  this service will be writen in ansi c to allow easy cross platform compilation. As an example ARM Linux.
  I will write a connector imediatly for VSafe. I will also write a command ine and a HTTP (REST) connector and any
  others as deemed necessary.
  
  
  
  
  
  
  
  
  
                
