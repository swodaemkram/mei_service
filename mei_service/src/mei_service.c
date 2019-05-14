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
char MEI_CURRENT_COMMAND[30] = "idle";
char tx_packet[30] = {0};


int main(int argc, char *argv[])
{

/*
==================================================================================================================
Lets process the service startup commands
==================================================================================================================
*/
	if (argv[1] == NULL){
			printf("Comm port must be supplied !\n\n");
			exit(1);
	}

		strncpy(comm_port,argv[1],strlen(argv[1]));
/*
===================================================================================================================
Finished processing the service startup commands
===================================================================================================================
Make Sure We Only Run Once
===================================================================================================================
*/
	FILE *pid_lock = NULL;                            	// declare pid lock file

		pid_lock = fopen("/run/mei_service.pid", "r");
		if (pid_lock != NULL){
			fclose(pid_lock);
			printf("\n mei_service is all ready running\n");
			exit(1);
		}

		pid_lock = fopen("/run/mei_service.pid", "w+");  	// Open the pid file for writing
		if (pid_lock == NULL){
		printf("\ncould not open lock file.\n");
		exit(1);
		}
		char strpid[6] = {0} ;
		int pid;
		pid = getpid();
		sprintf(strpid,"%d",pid);
		fwrite(strpid,1,sizeof(strpid),pid_lock);
		fclose(pid_lock);										// Close pid lock file

		log_Function("mei_service has started");
/*
======================================================================================================================
end of run once check
======================================================================================================================
We will prepare the serial port to setup communications
======================================================================================================================
*/
		int set_interface_attribs(int fd, int speed)
			{
			    struct termios tty;

			    if (tcgetattr(fd, &tty) < 0) {
			        printf("Error from tcgetattr: %s\n", strerror(errno));
			        return -1;
			    }

			    cfsetospeed(&tty, (speed_t)speed);
			    cfsetispeed(&tty, (speed_t)speed);

			    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
			    tty.c_cflag &= ~CSIZE;
			    tty.c_cflag |=  CS7;         /* 7-bit characters  pipes = yes ampersands and Tildes= no */
			    tty.c_cflag |=  PARENB;     /* even parity bit */
			    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
			    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

			    /* setup for non-canonical mode */

			    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
			    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
			    tty.c_oflag &= ~OPOST;

			    /* fetch bytes as they become available */
			    tty.c_cc[VMIN] = 1;
			    tty.c_cc[VTIME] = 1;

			    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
			        printf("Error from tcsetattr: %s\n", strerror(errno));
			        return -1;
			    }
			    return 0;
			}

			char *portname = comm_port;
			    int fd;
			    //int wlen;

			    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
			    if (fd < 0) {
			        printf("Error opening %s: %s\n", portname, strerror(errno));
			        exit(1);
			    }
			    /*baudrate 9600, 7 bits, even parity, 1 stop bit */
	set_interface_attribs(fd, B9600);
	log_Function(comm_port);
/*
======================================================================================================================
End of serial port setup
======================================================================================================================
*/
signal(SIGTERM,SignalHandler);

while(1){

unsigned int tx_crc = 0;

signal(SIGTERM,SignalHandler);

if (strcmp(rx_packet,"") == 0)//if the last RXed Packet is Blank Start a new polling session
{
	tx_packet[0] = '\x02';//stuff STX
	tx_packet[1] = '\x08' ;//Number of Bytes in the packet
	tx_packet[2] = '\x10' ;//Poll Command
	tx_packet[3] = '\x00' ;// No Data
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

if (rx_packet[2] == '\x20')
{
	tx_packet[2] = '\x11';
    tx_packet[6] = '\x00';
    tx_packet[7] = '\x00';
    tx_crc = 0;
    tx_crc = do_crc(tx_packet,8);
    tx_packet[6] = '\x03';
    tx_packet[7] = tx_crc;
}

if (rx_packet[2] == '\x21')
{
	tx_packet[2] = '\x10';
	tx_packet[6] = '\x00';
	tx_packet[7] = '\x00';
	tx_crc = 0;
	tx_crc = do_crc(tx_packet,8);
	tx_packet[6] = '\x03';
	tx_packet[7] = tx_crc;
}
//============================End of Polling================

mei_tx(tx_packet, comm_port); //Transmit Packet to MEI
mei_rx(comm_port); // Receive packet from MEI








//===========DEBUG CODE to print rx_packet===================
//int i = 0;
//while(i < rx_packet_len)
//{
//	printf("%02x|",rx_packet[i]);
//	i++;
//}
//printf("\n");
//============================END DEBUG CODE================

printf("%s\n",MEI_STATUS);
usleep(300000);

}//End of our while loop

close(fd);
return(0);
}
