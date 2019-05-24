/*
 * process_response.c
 *
 *  Created on: May 16, 2019
 *      Author: mark
 */

extern char rx_packet[40];
extern char MEI_STATUS[30];
char LAST_MEI_STATUS[30];
extern char MEI_CURRENT_COMMAND[30];
extern the_clean_text[30];

void process_response (void)
{

	switch(rx_packet[3])
	{

	case '\x00':
		  strcpy(MEI_STATUS,"idling");
		  break;
	case '\x01':
		  strcpy(MEI_STATUS,"accepting");
		  break;
	case '\x02':
		  strcpy(MEI_STATUS,"drawing_in");
		  break;
	case '\x04':
		  strcpy(MEI_STATUS,"escrowed");
		  break;
	case '\x08':
		  strcpy(MEI_STATUS,"stacking");
		  break;
	case '\x11':
		  strcpy(MEI_STATUS,"stacked");
		  break;
	case '\x20':
		  strcpy(MEI_STATUS,"processing");
		  break;
	case '\x41':
		  strcpy(MEI_STATUS,"returned");
		  break;

	}

	switch(rx_packet[2]) //Detect enhanced escrow
	{
	case '\x70':
		strcpy(MEI_STATUS,"escrowed");
		break;
	case '\x71':
		strcpy(MEI_STATUS,"escrowed");
		break;
	}
//===========================Detect Cassette Removal=========================================
    if (strncmp(MEI_STATUS,"stacked",7)==0 && rx_packet[5] == '\x00')
    {
    	strcpy(MEI_STATUS,"cassette_removed");
    }
//======================End of Cassette Removal Detection====================================
//============================Determine Dnom Stacked=========================================
/*    if (strncmp(MEI_STATUS,"stacked",7)==0 && rx_packet[5] != '\x00')//OLD IF Statement
    {
    	switch (rx_packet[5])
    	{
    	case '\x08':
    		strcpy(MEI_STATUS,"stacked_dnom_1"); //USD $1.00
    		break;
    	case '\x28':
    		strcpy(MEI_STATUS,"stacked_dnom_4"); //USD $20.00
    		break;
    	}
    }
*/
if (strncmp(MEI_STATUS,"escrowed",8)==0 && strncmp(MEI_CURRENT_COMMAND, "stack",5) == 0)
{
	char denom_detail[9] = {0};
	char temp_message[30] = {0};

	int v = 0;
	while(v <= 8)
	{
	  denom_detail[v] = rx_packet[v+11];
	 v++;
	}

clean_text(denom_detail,9);
sprintf(MEI_STATUS,"stacked a %s",the_clean_text);
//strncpy(MEI_STATUS,the_clean_text,8);
}
//=============================END of Dnom Determination====================================
//====================================Dnom Returned==========================================
    //log_Function(MEI_STATUS);
/*
    if (strncmp(MEI_STATUS,"returned",8)==0 )
    {
    	switch (rx_packet[5])
    	    	{
    	    	case '\x08':
    	    		strcpy(MEI_STATUS,"verified_dnom_1"); //USD $1.00
    	    		break;
    	    	case '\x28':
    	    		strcpy(MEI_STATUS,"verified_dnom_4"); //USD $20.00
    	    		break;
    	    	}
    }
*/
if (strncmp(MEI_STATUS,"escrowed",8)==0 && strncmp(MEI_CURRENT_COMMAND, "verify",5) == 0)
{
	char denom_detail[9] = {0};
	char temp_message[30] = {0};

	int v = 0;
	while(v <= 8)
	{
	  denom_detail[v] = rx_packet[v+11];
	 v++;
	}

clean_text(denom_detail,9);
sprintf(MEI_STATUS,"Verified a %s",the_clean_text);
//strncpy(MEI_STATUS,the_clean_text,8);
}
//=================================End of Dnom Returned=====================================
//==========================LOG ONLY CHANGES IN STATUS=======================================
if (strcmp(MEI_STATUS,LAST_MEI_STATUS)!=0)
{
	char log_message[45] = {0};
	sprintf(log_message,"MEI Response = %s",MEI_STATUS);
	log_Function(log_message);
	domain_response_server();
	strcpy(LAST_MEI_STATUS,MEI_STATUS);
}
//============================END OF STATUS LOGGING==========================================

	return;
}
