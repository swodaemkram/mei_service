/*
 ===============================================================================================================
 Name        : mei_service.c
 Author      : Mark Meadows
 Version     :
 Copyright   : Copyright (c) 2019 Fireking Security Group
 Description : mei_service in C, Ansi-style
 ================================================================================================================
 */
# include "mei_service.h"

char comm_port[250] = {0};
char tx_packet[30] = {0};
char pid_loc_file_name[250];
char MEI_CURRENT_COMMAND[30] = "idle";
int procnumber;

int main(int argc, char *argv[])
{
/*
==================================================================================================================
Lets process the service startup commands
==================================================================================================================
*/
	if (argv[1] == NULL){
			printf("Comm port must be supplied !\n\n");
			SignalHandler(1);
	}

		strncpy(comm_port,argv[1],strlen(argv[1]));

	if (argv[2] == NULL){
		printf("Must have Instance Number ! \n\n");
		SignalHandler(1);
	}


procnumber = atoi(argv[2]);

sprintf(pid_loc_file_name,"/run/mei_service%d.pid",procnumber);
//printf("pid-file = %s\n",pid_loc_file_name);//DEBUG
/*
===================================================================================================================
Finished processing the service startup commands
===================================================================================================================
Make Sure We Only Run Once
===================================================================================================================
*/
	FILE *pid_lock = NULL;                            	// declare pid lock file

		//pid_lock = fopen("/run/mei_service.pid", "r");
		pid_lock = fopen(pid_loc_file_name,"r");
		if (pid_lock != NULL){
			fclose(pid_lock);
			printf("\n mei_service is all ready running on this process id\n");
			SignalHandler(1);
		}

		//pid_lock = fopen("/run/mei_service.pid", "w+");  	// Open the pid file for writing

		pid_lock = fopen(pid_loc_file_name,"w+");
		if (pid_lock == NULL){
		printf("\ncould not open lock file.\n");
		SignalHandler(1);
		}
		char strpid[6] = {0} ;
		int pid;
		pid = getpid();
		sprintf(strpid,"%d",pid);
		fwrite(strpid,1,sizeof(strpid),pid_lock);
		fclose(pid_lock);										// Close pid lock file
/*
======================================================================================================================
end of run once check
======================================================================================================================
*/

log_Function("================================================");
char log_message[30];
sprintf(log_message,"MEI Service Starting using %s",comm_port);
log_Function(log_message);
log_Function("Ver 01.88.00");
log_Function("================================================");
signal(SIGTERM,SignalHandler);

while(1){

unsigned int tx_crc = 0;

signal(SIGTERM,SignalHandler);

if (strcmp(rx_packet,"") == 0)//if the last RXed Packet is Blank Start a new polling session
{
	tx_packet[0] = '\x02';//stuff STX
	tx_packet[1] = '\x08' ;//Number of Bytes in the packet
	tx_packet[2] = '\x10' ;//Poll Command
	tx_packet[3] = '\x10' ;// No Data
	tx_packet[4] = '\x00' ;// No Data
	tx_packet[5] = '\x00' ;// No Data
	tx_packet[6] = '\x00' ;// Set a space for the ETX
	tx_packet[7] = '\x00' ;// Set a space for the CRC
	tx_crc = do_crc(tx_packet,8);
	tx_packet[6] = '\x03' ;// Insert ETX into packet
	tx_packet[7] = tx_crc ;// Insert CRC into packet
}
//log_Function(tx_packet);//DEBUG data to log file
//printf("\n%02x|%02x|%02x|%02x|%02x|%02x|%02x|%02x\n",tx_packet[0],tx_packet[1],tx_packet[2],tx_packet[3],tx_packet[4],tx_packet[5],tx_packet[6],tx_packet[7]); //DEBUG CODE
//\x02\x08\x10\x1f\x14\x00 // Use this Packet template to get MEI to accept bills

//==================Start of Polling========================

if (rx_packet[2] == '\x20') //Standard Polling
{
	tx_packet[2] = '\x11';
    tx_packet[6] = '\x00';
    tx_packet[7] = '\x00';
    tx_crc = 0;
    tx_crc = do_crc(tx_packet,8);
    tx_packet[6] = '\x03';
    tx_packet[7] = tx_crc;
}

if (rx_packet[2] == '\x21') //Standard Polling
{
	tx_packet[2] = '\x10';
	tx_packet[6] = '\x00';
	tx_packet[7] = '\x00';
	tx_crc = 0;
	tx_crc = do_crc(tx_packet,8);
	tx_packet[6] = '\x03';
	tx_packet[7] = tx_crc;
}

if (rx_packet[2] == '\x70') //Enhanced Information Polling
{
	tx_packet[2] = '\x11';
    tx_packet[6] = '\x00';
    tx_packet[7] = '\x00';
    tx_crc = 0;
    tx_crc = do_crc(tx_packet,8);
    tx_packet[6] = '\x03';
    tx_packet[7] = tx_crc;
}

if (rx_packet[2] == '\x71') //Enhanced Information Polling
{
	tx_packet[2] = '\x10';
	tx_packet[6] = '\x00';
	tx_packet[7] = '\x00';
	tx_crc = 0;
	tx_crc = do_crc(tx_packet,8);
	tx_packet[6] = '\x03';
	tx_packet[7] = tx_crc;
}
//==================End of Polling=============================
//===============Business  Logic for MEI=======================
domain_socket_server();       //Get Command from domain socket
//log_Function("domain_socket_server");//DEBUG
process_commands();           //Process In coming commands
//log_Function("process_command");//DEBUG
mei_tx(tx_packet, comm_port); //Transmit Packet to MEI
//log_Function("mei_tx");       //DEBUG
mei_rx(comm_port);            // Receive packet from MEI
//log_Function("mei_rx");       //DEBUG
process_response();           // What does the Response from the MEI mean   <-------------------------------|
//log_Function("process_response");//DEBUG                                                                  |
domain_response_server();     // Send Translated response from MEI to domain socket: This gets  here now -|
//log_Function("domain_response_server called");//DEBUG
//===============END OF Business Logic===========================
//===============Process Stop Command============================
if(strncmp(MEI_CURRENT_COMMAND,"stop",4)==0)
{
 	log_Function("================================================");
	log_Function("Stop Command Received Shutting Down Service ....");
 	log_Function("================================================");
	SignalHandler(1);
}
//================End of Stop Command=============================
usleep(300000);

}//End of our while loop
//close(fd);
return(0);
}
