/*
 * mei_rx.c
 *
 *  Created on: May 13, 2019
 *      Author: mark
 */


#include <termios.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>


char * mei_rx(char *comm_port)

{
/*
======================================================================================================================
Setup Comm Port
======================================================================================================================
*/
	char rx_packet[30] = {0};
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



/*
================================================================================================================
Finished Setting up Comm Port
================================================================================================================
*/
			printf("\033[1;32m"); //Set color to Green

			//do {
			    unsigned char buf[80];
			    int rdlen;
			    int i = 0;

			    rdlen = read(fd, buf, sizeof(buf) - 1);
			    if (rdlen > 0) {

			    	while(i < rdlen)
			    	{
			    		rx_packet[i] = buf[i];
			    		printf("%02x|",rx_packet[i]);
			    		i++;
			    	}
			    	printf("\033[0m\n");  //Set Color back to white

			    }
/*
=================================================================================================================
Got RX Data Need to Check CRC
=================================================================================================================
*/
char crc_check_packet[] = {0};
i = 0;
int calculated_crc = 0;
char ok[4] = "ok";

while (i < rdlen)
{
	crc_check_packet[i] = rx_packet[i];
	i++;
}
	crc_check_packet[rdlen - 1] = '\x00';
	crc_check_packet[rdlen - 2] = '\x00';
	calculated_crc = do_crc(crc_check_packet,rdlen);
	printf("Calculated CRC = %02x\n",calculated_crc);
	if (calculated_crc != rx_packet[rdlen])
	{
		return(ok) ;
	}

/*
=================================================================================================================
End of CRC Check
=================================================================================================================
 */
	i=0;
	while(i<rdlen)
	{
		LAST_PACKET[i] = rx_packet[i] ;
		i++;
	}

	return(ok) ;

}
