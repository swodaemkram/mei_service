/*
 * Signal_Handler.c
 *
 *  Created on: May 13, 2019
 *      Author: mark
 */

void SignalHandler(int signum)

{
			remove("/run/mei_service.pid");
			log_Function("teminate signal received shutting mei service down");

			exit(0);
}
