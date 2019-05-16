/*
 * process_response.c
 *
 *  Created on: May 16, 2019
 *      Author: mark
 */

extern char rx_packet[30];
extern char MEI_STATUS[30];

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
//------------------------------Detect Cassette Removal---------------------------------------
    if (strncmp(MEI_STATUS,"stacked",7)==0 && rx_packet[5] == '\x00')
    {
    	strcpy(MEI_STATUS,"cassette_removed");
    }
//---------------------------End of Cassette Removal Detection--------------------------------




	return;
}
