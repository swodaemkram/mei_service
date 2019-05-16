/*
 * detailed_info_command.c
 *
 *  Created on: May 16, 2019
 *      Author: mark
 */
extern char tx_packet[30];
extern char rx_packet[30];
extern char comm_port[250];

void detailed_info_command(void)
{
	tx_packet[0] = '\x02';
	tx_packet[1] = '\x08';
	tx_packet[2] = '\x60';
	tx_packet[3] = '\x00';
	tx_packet[4] = '\x00';
	tx_packet[5] = '\x04';
	tx_packet[6] = '\x03';
	tx_packet[7] = '\x6c';

	mei_tx(tx_packet,comm_port);
	mei_rx(comm_port);
    clean_text(rx_packet,sizeof(rx_packet));
    _





	return;

}
