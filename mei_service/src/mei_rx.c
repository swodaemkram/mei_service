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

char rx_packet[30] = {0};
int  rx_packet_len = 0;
char MEI_STATUS[30] = "idling";
int is_comm_port_open = 0;

void mei_rx(char *comm_port)

{
//printf("MEI_RX CALLED\n");//DEBUG

/*
======================================================================================================================
Setup Comm Port
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

/*
================================================================================================================
Finished Setting up Comm Port
================================================================================================================
*/
			    fcntl(fd, F_SETFL, FNDELAY);//THIS IS HUGELY IMPORTANT !!! MAKES THE SERIALPORT NON-BLOCKING

			    printf("\033[1;32m"); //Set color to Green

			    unsigned char buf[80];
			    int rdlen = 0;
			    int i = 0;


			    rdlen = read(fd, buf, sizeof(buf) -1);//Get Data from Comm Port was -1


			    if (rdlen > 0) {

			    	while(i < rdlen)
			    	{
			    		rx_packet[i] = buf[i];
			    		printf("%02x|",rx_packet[i]);//Print The RXed Hex Packet
			    		i++;
			       	}
			    	printf("\033[0m");  //Set Color back to white

			    }


			    rx_packet_len = rdlen;

			    if (rx_packet_len < 1)
			    {
			    	rx_packet[0] = '\x00';
			    	rx_packet_len = 1;
			    	printf("\033[0m");  //Set Color back to white
			    }

/*
=================================================================================================================
Got RX Data Need to Check CRC
=================================================================================================================
*/
char crc_check_packet[] = {0};
 i = 0;
int calculated_crc = 0;

while (i < rx_packet_len)
{
	crc_check_packet[i] = rx_packet[i];
	i++;
}
	crc_check_packet[rx_packet_len - 1] = '\x00';
	crc_check_packet[rx_packet_len - 2] = '\x00';
	calculated_crc = do_crc(crc_check_packet,rx_packet_len);
	//printf("Calculated CRC = %02x\n",calculated_crc);
	if (calculated_crc != rx_packet[rx_packet_len-1])
	{
		rx_packet[0] = '\x00';
		rx_packet_len = 1;
		printf("BAD CRC RXed\n");
		log_Function("BAD CRC RXed !");
		return;
	}

/*
=================================================================================================================
End of CRC Check
=================================================================================================================
Get RXed Status of MEI
=================================================================================================================
*/

if (rx_packet_len <= 1)
{
	strcpy(MEI_STATUS,"dissconnected");
	log_Function(MEI_STATUS);
	return;
}

/*
=================================================================================================================
END of Getting Status from MEI
=================================================================================================================
*/
close(fd);
return;
}





