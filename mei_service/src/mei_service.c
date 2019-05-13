/*
 ===============================================================================================================
 Name        : mei_service.c
 Author      : Mark Meadows
 Version     :
 Copyright   : Copyright (c) 2019 Fireking Security Group
 Description : mei_service in C, Ansi-style
 ================================================================================================================
 */
# include "mei_service.h"

int main(int argc, char *argv[])
{
/*
===================================================================================================================
Make Sure We Only Run Once
===================================================================================================================
*/
	FILE *pid_lock = NULL;                            	// declare pid lock file

		pid_lock = fopen("/run/mei_service.pid", "r");
		if (pid_lock != NULL){
			fclose(pid_lock);
			printf("\n mei_service is all ready running\n");
			exit(1);
		}

		pid_lock = fopen("/run/mei_service.pid", "w+");  	// Open the pid file for writing
		if (pid_lock == NULL){
		printf("\ncould not open lock file.\n");
		exit(1);
		}
		char strpid[6] = {0} ;
		int pid;
		pid = getpid();
		sprintf(strpid,"%d",pid);
		fwrite(strpid,1,sizeof(strpid),pid_lock);
		fclose(pid_lock);										// Close pid lock file

		log_Function("mei_service has started");
/*
======================================================================================================================
end of run once check
======================================================================================================================
We will prepare the serial port to setup communications
======================================================================================================================
*/







/*
======================================================================================================================
End of serial port setup
======================================================================================================================
*/
while(1){







	}//End of our while loop


return(0);
}
