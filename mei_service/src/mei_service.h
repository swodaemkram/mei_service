/*
 * mei_service.h
 *
 *  Created on: May 13, 2019
 *      Author: mark
 */

#ifndef MEI_SERVICE_H_
#define MEI_SERVICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

/* baudrate settings are defined in <asm/termbits.h>, which is
included by <termios.h> */
#define BAUDRATE B9600
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
/* MEI Constants */

	// Byte 0 Status
int MEI_ACCEPTING = 0x02;
int MEI_ESCROW    = 0x04;
int MEI_STACKING  = 0x08;
int MEI_STACKED   = 0x10;
int MEI_RETURNING = 0x20;
int MEI_RETURNED  = 0x40;
	// Byte 1 Status
int MEI_CHEATED   = 0x01;
int MEI_REJECTED  = 0x02;
int MEI_JAM	   = 0x04;
int MEI_FULL	   = 0x08;
int MEI_CASSETTE  = 0x10;
	// Byte 2 Status
int MEI_POWERUP   = 0x01;
int MEI_FAILURE   = 0x04;
	// Byte 3 Status
int MEI_DOWNLOADING = 0x02;
	// Commands
int	MEI_POLL      = 0x10;
int	MEI_STACK     = 0x30;
int	MEI_RETURN    = 0x50;
	// Command Types
int	MEI_CMD       = 0x10;
//	MEI_REPLY     = 0x20;
int	MEI_DOWNLOAD  = 0x50;
int	unsigned MEI_AUX       = 0x60;
	// Auxiliary command sub-types
unsigned int	MEI_GETMODEL  = 0x04;
unsigned int    MEI_GETSERIAL = 0x05;
unsigned int	MEI_GETBOOTVER	= 0x06;
unsigned int	MEI_GETAPPVER = 0x07;
unsigned int	MEI_GETVARNAME	= 0x08;
unsigned int	MEI_GETVERSION	= 0x09;
unsigned int	MEI_GETQP		= 0x0B;
unsigned int	MEI_GETPERF   =  0x0C;
unsigned int	MEI_GETBNF		= 0x10;
unsigned int	MEI_RESET		= 0x7F;
unsigned int	MEI_EXT       =  0x70;

// Extension command sub-types
int	MEI_GETBILLS  =  0x02;
int	MEI_RETRIEVE  =  0x0B;
int	MEI_BOOKMARK = 0x0D;


//--------------------------------All Available Functions------------------------
void log_Function(char *log_message); //provides logging service for mei_service
void SignalHandler(int signum); //provides signal handling for the service
int do_crc(char buff[], int buffer_len); //Implementation of the MEI XOR Check Sum
void mei_tx(char* packet, char* comm_port); //Sends data to MEI
void mei_rx(char* com_port); //Rx Data from MEI
void get_command_from_file(void);//Read a command from a file
//--------------------------------End of Available Functions---------------------

//--------------------------------Global Variables-------------------------------
extern char MEI_STATUS[30]; //GLOBAL STATUS OF THE MEI
extern char MEI_CURRENT_COMMAND[30]; //Global Current command being processing
extern char LAST_PACKET[30]; //Global Last RXed Packet
extern char comm_port[250]; //Comm Port passed by command line
extern char rx_packet[30]; //Global RX Packet
extern int rx_packet_len; //Global Length of RXed Packet
extern char tx_packet[30];//Global TX packet
extern int is_comm_port_open;

//---------------------------------END Of Global Variables-----------------------


#endif /* MEI_SERVICE_H_ */
