/*
 * Signal_Handler.c
 *
 *  Created on: May 13, 2019
 *      Author: mark
 */

extern char pid_loc_file_name[250];
extern char mei_command_sock_name[250];
extern char mei_command_file_name[250];
extern char mei_response_sock_name[250];

void SignalHandler(int signum)

{
			//remove("/run/mei_service.pid");
			remove(pid_loc_file_name);
			remove(mei_command_sock_name);
			remove(mei_response_sock_name);
			log_Function("teminate signal received shutting mei service down");
			exit(0);
}
