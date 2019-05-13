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

char MEI_STATUS[30]= {0}; //GLOBAL STATUS OF THE MEI

int main(int argc, char *argv[])
{

char comm_port[250] = {0}; //Comm Port passed by command line

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
signal(SIGTERM,SignalHandler);








}//End of our while loop


return(0);
}
