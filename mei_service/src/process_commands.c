/*
 * process_commands.c
 *
 *  Created on: May 16, 2019
 *      Author: mark
 */
extern char MEI_CURRENT_COMMAND[30];
extern char tx_packet[30];
extern char MEI_STATUS[30];
extern char rx_packet[30];
char MEI_LAST_COMMAND[30] = {0};
int GET_MODEL_ONETIME = 0;
int GET_INFO_ONETIME = 0;
int GET_SERIAL_ONETIME = 0;
int GET_BOOTVER_ONETIME = 0;
int GET_APPVER_ONETIME = 0;
int GET_VARNAME_ONETIME = 0;
int DEBUG_LOG = 0; //Turns on and off detailed debug logging
int DEBUG_LOG_ONETIME = 0;

void process_commands(void)
{

	unsigned int tx_crc = 0;

//===============================Start of Stack Command=========================================
if(strncmp(MEI_CURRENT_COMMAND,"stack",5)==0) //Has the "stack" command been RXed
	{
		tx_packet[3] = '\x1f';
		tx_packet[4] = '\x14';
		tx_packet[5] = '\x10'; //DEBUG FOR NEW ENHANCED BILL REPORTING '\x10' for enhanced '\x00' for non-enhanced
		tx_packet[6] = '\x00';
		tx_packet[7] = '\x00';
		tx_crc = 0;
		tx_crc = do_crc(tx_packet,8);
		tx_packet[6] = '\x03';
		tx_packet[7] = tx_crc;
	}
/* I LIKED THIS WAY BETTER
if(strncmp(MEI_CURRENT_COMMAND,"stack",5)==0 && strncmp(MEI_STATUS,"escrowed",8)==0)

	{
		tx_packet[3] = '\x7f';//We are sending the Stack Command in this part
		tx_packet[4] = '\x3c';
		tx_packet[6] = '\x00';
		tx_packet[7] = '\x00';
		tx_crc = 0;
		tx_crc = do_crc(tx_packet,8);
		tx_packet[6] = '\x03';
		tx_packet[7] = tx_crc;

	}
*/

if((strncmp(MEI_CURRENT_COMMAND,"stack",5)==0 && rx_packet[11]=='\x55') ||(strncmp(MEI_CURRENT_COMMAND,"stack",5)==0 && rx_packet[11]=='\x45') || (strncmp(MEI_CURRENT_COMMAND,"stack",5)==0 && rx_packet[11]=='\x49')) //Detects the U in USD, THE E in ERO and the I in ILS
{
	        tx_packet[3] = '\x7f';//We are sending the Stack Command in this part
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
	     		tx_packet[3] = '\x00'; //We are sending the idle Command in this part
				tx_packet[4] = '\x00';
				tx_packet[6] = '\x00';
				tx_packet[7] = '\x00';
				tx_crc = 0;
				tx_crc = do_crc(tx_packet,8);
				tx_packet[6] = '\x03';
				tx_packet[7] = tx_crc;

	}
//===============================END OF Idle Command=============================================
//=====================================Reset Command=============================================
		if(strncmp(MEI_CURRENT_COMMAND,"reset",5)== 0 && strncmp(MEI_STATUS, "accepting",9) == 0 )
		{
							tx_packet[2] = '\x60';        //Expanded Command Mode
                			tx_packet[3] = '\x7f';        //We are sending the reset Command
							tx_packet[4] = '\x7f';        //"\x02\x08\x60\x7f\x7f\x7f\x03"
							tx_packet[5] = '\x7f';
							tx_packet[6] = '\x00';
							tx_packet[7] = '\x00';
							tx_crc = 0;
							tx_crc = do_crc(tx_packet,8);
							tx_packet[6] = '\x03';
							tx_packet[7] = tx_crc;
							sleep(3);

		}
//==================================END of Reset Command=========================================
//=================================Start of Verify Command=======================================
         if(strncmp(MEI_CURRENT_COMMAND,"verify",6)== 0 && strncmp(MEI_STATUS,"escrowed") != 0)

         {
        	 tx_packet[3] = '\x1f';
        	 tx_packet[4] = '\x14';
        	 tx_packet[5] = '\x10';//WAS '\x00'
        	 tx_packet[6] = '\x00';
        	 tx_packet[7] = '\x00';
        	 tx_crc = 0;
        	 tx_crc = do_crc(tx_packet,8);
        	 tx_packet[6] = '\x03';
        	 tx_packet[7] = tx_crc;
         }
/*
         if(strncmp(MEI_CURRENT_COMMAND,"verify",6) == 0 && strncmp(MEI_STATUS,"escrowed") == 0)

         {

        	 tx_packet[3] = '\x00';
        	 tx_packet[4] = '\x5c';    //Return Document Command
        	 tx_packet[5] = '\x00';
        	 tx_packet[6] = '\x00';
        	 tx_packet[7] = '\x00';
        	 tx_crc = 0;
        	 tx_crc = do_crc(tx_packet,8);
        	 tx_packet[6] = '\x03';
        	 tx_packet[7] = tx_crc;

         }
*/

 if((strncmp(MEI_CURRENT_COMMAND,"verify",6)== 0 && rx_packet[11]=='\x55') ||(strncmp(MEI_CURRENT_COMMAND,"verify",6)== 0 && rx_packet[11]=='\x45' )||(strncmp(MEI_CURRENT_COMMAND,"verify",6)== 0 && rx_packet[11]=='\x49')) //Detects the U in USD, THE E in ERO and the I in ILS

 {
			 tx_packet[3] = '\x00';
         	 tx_packet[4] = '\x5c';    //Return Document Command
         	 tx_packet[5] = '\x00';
         	 tx_packet[6] = '\x00';
         	 tx_packet[7] = '\x00';
         	 tx_crc = 0;
         	 tx_crc = do_crc(tx_packet,8);
         	 tx_packet[6] = '\x03';
         	 tx_packet[7] = tx_crc;

   }

//==================================End of Verify  Command=======================================
//===============================LOG ONLY CHANGES================================================
	if(strcmp(MEI_CURRENT_COMMAND,MEI_LAST_COMMAND)!= 0)
	{
		char log_message[250] ={0};
		sprintf(log_message,"Command Issued = %s",MEI_CURRENT_COMMAND);
		log_Function(log_message);
		strcpy(MEI_LAST_COMMAND,MEI_CURRENT_COMMAND);
		GET_MODEL_ONETIME = 0; //Reset Run Command Once Flag
		GET_SERIAL_ONETIME = 0;//Reset Run Command Once Flag
		GET_BOOTVER_ONETIME = 0;//Reset Run Command Once Flag
		GET_APPVER_ONETIME = 0;//Reset Run Command Once Flag
		GET_VARNAME_ONETIME = 0;//Reset Run Command Once Flag
		DEBUG_LOG_ONETIME = 0;
	}
//==================================END OF LOGGING===============================================
// ^^^^^^^^^^^^ ALL SINGLE RUN COMMANDS NEED TO BE BELOW THIS  ^^^^^^^^^^^^^^^^
//=================================Get Serial Command============================================
    if(strncmp(MEI_CURRENT_COMMAND,"serial",6)== 0 && GET_SERIAL_ONETIME == 0)
   	{
    	get_serial();
   	}
//==================================End of Get Serial command====================================
//===============================GET MODEL Command===============================================
    if(strncmp(MEI_CURRENT_COMMAND,"model",5)== 0 && GET_MODEL_ONETIME == 0)
   	{
       	get_model();
   	}
//=================================End of GET MODEL command======================================
//=================================Get BOOT Version==============================================
    if(strncmp(MEI_CURRENT_COMMAND,"bootver",7)== 0 && GET_BOOTVER_ONETIME == 0)
  	{
       	get_bootver();
   	}
//==================================END of Get Boot Version======================================
//==================================Get APPVER Command===========================================
    if(strncmp(MEI_CURRENT_COMMAND,"appver",6)== 0 && GET_APPVER_ONETIME == 0)
    {
       	get_appver();
    }
//==================================END of Get APPVER Command====================================
//==================================Get VARNAME Command===========================================
     if(strncmp(MEI_CURRENT_COMMAND,"varname",6)== 0 && GET_VARNAME_ONETIME == 0)
     {
       	get_varname();
     }
//==================================END of Get APPVER Command====================================
//==================================Toggel DEBUG logging=========================================
     if (strncmp(MEI_CURRENT_COMMAND,"debuglog",8)== 0 && DEBUG_LOG_ONETIME == 0)
     {
    	 switch(DEBUG_LOG)
    	 {
    	 case 1:
    		 DEBUG_LOG = 0;
    		 log_Function("DEBUG LOGGING TURNED OFF");
    		 DEBUG_LOG_ONETIME = 1;
    		 break;
    	 case 0:
    		 DEBUG_LOG = 1;
    		 log_Function("DEBUG LOGGING TURNED ON");
    		 DEBUG_LOG_ONETIME =1;
    		 break;
       	 }
     }
//==========================================END of DEBUG logging==================================
   return;
}
