/*
 * process_commands.c
 *
 *  Created on: May 16, 2019
 *      Author: mark
 */
extern char MEI_CURRENT_COMMAND[30];
extern char tx_packet[30];
extern char MEI_STATUS[30];
char MEI_LAST_COMMAND[30] = {0};

void process_commands(void)
{

	unsigned int tx_crc = 0;

//===============================Start of Stack Command=========================================
	if(strncmp(MEI_CURRENT_COMMAND,"stack",5)==0) //Has the "stack" command been RXed
	{
		tx_packet[3] = '\x1f';
		tx_packet[4] = '\x14';
		tx_packet[6] = '\x00';
		tx_packet[7] = '\x00';
		tx_crc = 0;
		tx_crc = do_crc(tx_packet,8);
		tx_packet[6] = '\x03';
		tx_packet[7] = tx_crc;
	}
	if(strncmp(MEI_CURRENT_COMMAND,"stack",5)==0 && strncmp(MEI_STATUS,"escrowed",8)==0)
	{
		tx_packet[3] = '\x7f';                   //We are sending the Stack Command in this part
		tx_packet[4] = '\x3c';
		tx_packet[6] = '\x00';
		tx_packet[7] = '\x00';
		tx_crc = 0;
		tx_crc = do_crc(tx_packet,8);
		tx_packet[6] = '\x03';
		tx_packet[7] = tx_crc;
	}
//============================END OF Stacking Service============================================
//============================Start of Idle Command==============================================

	if(strncmp(MEI_CURRENT_COMMAND,"idle",4)==0 && strncmp(MEI_STATUS, "escrowed",8)!=0)//We dont want to idle with money escrowed
	{
	     		tx_packet[3] = '\x00';                   //We are sending the idle Command in this part
				tx_packet[4] = '\x00';
				tx_packet[6] = '\x00';
				tx_packet[7] = '\x00';
				tx_crc = 0;
				tx_crc = do_crc(tx_packet,8);
				tx_packet[6] = '\x03';
				tx_packet[7] = tx_crc;

	}
//===============================END OF Idle Command=============================================
//===============================LOG ONLY CHANGES================================================
	if(strcmp(MEI_CURRENT_COMMAND,MEI_LAST_COMMAND)!= 0)
	{
		log_Function(MEI_CURRENT_COMMAND);
		strcpy(MEI_LAST_COMMAND,MEI_CURRENT_COMMAND);
	}
//==================================END OF LOGGING===============================================
	return;
}
