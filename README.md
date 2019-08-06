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
 reset
 verify
 stack
 idle
 appver
 bootver
 model
 serial
 varname
 
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

-----------------------------------------------------------------------------------------------------
Test command for connection and issuing commands until a client is writen
sudo socat -UNIX-CONNECT:./mei_service.sock
------------------------------------------------------------------------------------------------------
                
  this service will be writen in ansi c to allow easy cross platform compilation. As an example ARM Linux.
  I will write a connector imediatly for VSafe. I will also write a command ine and a HTTP (REST) connector and any
  others as deemed necessary.
  
  a new program called meicli is a new command line "connector" for the mei_service it connects to the Domain Socket 
  monitored by mei_service and allows a user to issue a command that is sent to the mei_servers API and allows control 
  of the service from the command line. (finished on 10/24/2019).
  
  <hr>
  
  This program is now a multi-instance service and the CLI usage is as follows
  
  sudo ./mei_service /dev/ttyUSB0 1
  
  then use usdo ./meicli 1 {command} to manage the service
  
  
  
  
  
  
  
  
                
