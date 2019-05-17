/*
 * detailed_info_command.c
 *
 *  Created on: May 16, 2019
 *      Author: mark
 */
extern char tx_packet[30];
extern char rx_packet[30];
extern char comm_port[250];
extern int GET_INFO_ONETIME;
extern char the_clean_text[30];

void detailed_info_command(void)
//=========================GET MODEL===========================

{

	tx_packet[0] = '\x02';//|
	tx_packet[1] = '\x08';//|
	tx_packet[2] = '\x60';//|
	tx_packet[3] = '\x00';//|---------Get Model Command
	tx_packet[4] = '\x00';//|
	tx_packet[5] = '\x04';//|
	tx_packet[6] = '\x03';//|
	tx_packet[7] = '\x6c';//|

	while(rx_packet[2] != '\x60')//We need the MEI to Send us back an INFO packet
	{
	mei_tx(tx_packet,comm_port);
	usleep(100000);//Slow down we were going too fast
	mei_rx(comm_port);
    clean_text(rx_packet,sizeof(rx_packet));//Clean up the model number
	}

	char log_message[30] = {0};
	sprintf(log_message,"MEI Response for Model = %s",the_clean_text);
	log_Function(log_message);//For now we will print the model number in the Log file but could put it any place

//=========================END GET MODEL=======================
/*
//=========================Serial Number=======================
	tx_packet[0] = '\x02';//|
	tx_packet[1] = '\x08';//|
	tx_packet[2] = '\x60';//|
	tx_packet[3] = '\x00';//|---------Get Serial Command
	tx_packet[4] = '\x00';//|
	tx_packet[5] = '\x05';//|
	tx_packet[6] = '\x03';//|
	tx_packet[7] = '\x6d';//|

	while(rx_packet[2] != '\x60')//We need the MEI to Send us back an INFO packet
	{
	mei_tx(tx_packet,comm_port);
	usleep(100000);//Slow down we were going too fast
	mei_rx(comm_port);
	clean_text(rx_packet,sizeof(rx_packet));//Clean up the Serial number
	}
	bzero(log_message,30);
	sprintf(log_message,"MEI Response for Serial Number = %s",the_clean_text);
	log_Function(log_message);//For now we will print the Serial number in the Log file but could put it any place
//==============================END of Serial Number===================
*/

GET_INFO_ONETIME = 1;    //Keeps this from spinning out of control
tx_packet[2] = '\x10';   //Put tx_packet back in command mode
return;
}
