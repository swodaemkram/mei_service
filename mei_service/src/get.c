/*
 * get.c
 *
 *  Created on: Jun 5, 2019
 *      Author: mark
 */

extern char MEI_CURRENT_COMMAND[30];
extern char tx_packet[30];
extern char rx_packet[40];
extern char comm_port[250];
extern int GET_ONETIME;
extern char the_clean_text[30];
extern char MEI_STATUS[30];

void get(void)

{
//===================These things are handled in other methods==============================
	    if (GET_ONETIME == 1) return;
       	if (strncmp(MEI_CURRENT_COMMAND,"reset",5)== 0) return;
		if (strncmp(MEI_CURRENT_COMMAND,"stack",5)== 0) return;
		if (strncmp(MEI_CURRENT_COMMAND,"verify",5)== 0) return;
		if (strncmp(MEI_CURRENT_COMMAND,"idle",4)== 0) return;
//===================These things are handled in other methods==============================

		if (strncmp(MEI_CURRENT_COMMAND,"appver",6) == 0) tx_packet[5] = '\x07';
       	if (strncmp(MEI_CURRENT_COMMAND,"bootver",7) == 0) tx_packet[5] = '\x06';
       	if (strncmp(MEI_CURRENT_COMMAND,"model",5) == 0) tx_packet[5] = '\x04';
       	if (strncmp(MEI_CURRENT_COMMAND,"serial",6) == 0) tx_packet[5] = '\x05';
       	if (strncmp(MEI_CURRENT_COMMAND,"varname",7) == 0) tx_packet[5] = '\x08';

	    tx_packet[0] = '\x02';//|
		tx_packet[1] = '\x08';//|
		tx_packet[2] = '\x60';//|
		tx_packet[3] = '\x00';//|---------Get Command
		tx_packet[4] = '\x00';//|
		//tx_packet[5] = '\x08';//|
		tx_packet[6] = '\x00';//|
		tx_packet[7] = '\x00';//|

		int newcrc = do_crc(tx_packet,8);
		tx_packet[6] = '\x03';
		tx_packet[7] = newcrc;

		while(rx_packet[2] != '\x60')//We need the MEI to Send us back an INFO packet
		{
		mei_tx(tx_packet,comm_port);
		usleep(100000);//Slow down we were going too fast
		mei_rx(comm_port);
	    clean_text(rx_packet,sizeof(rx_packet));//Clean up the Variant Name
		}

		char log_message[100] = {0};
		sprintf(log_message,"MEI Response = %s",the_clean_text);
		strcpy(MEI_STATUS,the_clean_text);
		domain_response_server();
		log_Function(log_message);//For now we will print the response in the Log file but could put it any place
		tx_packet[2] = '\x10';    //Put tx_packet back in command mode
		GET_ONETIME = 1;    //Keeps this from spinning out of control
		tx_packet[2] = '\x10';    //Put tx_packet back in command mode

	return;
}
