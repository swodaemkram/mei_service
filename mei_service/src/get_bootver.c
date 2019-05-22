/*
 * get_bootver.c
 *
 *  Created on: May 17, 2019
 *      Author: mark
 */

extern char tx_packet[30];
extern char rx_packet[40];
extern char comm_port[250];
extern int GET_BOOTVER_ONETIME;
extern char the_clean_text[30];
extern char MEI_STATUS[30];

void get_bootver(void)

{
	    tx_packet[0] = '\x02';//|
		tx_packet[1] = '\x08';//|
		tx_packet[2] = '\x60';//|
		tx_packet[3] = '\x00';//|---------Get Boot Version Command
		tx_packet[4] = '\x00';//|
		tx_packet[5] = '\x06';//|
		tx_packet[6] = '\x03';//|
		tx_packet[7] = '\x6e';//|

		while(rx_packet[2] != '\x60')//We need the MEI to Send us back an INFO packet
		{
		mei_tx(tx_packet,comm_port);
		usleep(100000);//Slow down we were going too fast
		mei_rx(comm_port);
	    clean_text(rx_packet,sizeof(rx_packet));//Clean up the model number
		}

		char log_message[100] = {0};
		sprintf(log_message,"MEI Response Boot Version = %s",the_clean_text);
		strcpy(MEI_STATUS,the_clean_text);
		domain_response_server();
		log_Function(log_message);//For now we will print the model number in the Log file but could put it any place
		tx_packet[2] = '\x10';    //Put tx_packet back in command mode
		GET_BOOTVER_ONETIME = 1;    //Keeps this from spinning out of control
		tx_packet[2] = '\x10';    //Put tx_packet back in command mode

	return;
}
