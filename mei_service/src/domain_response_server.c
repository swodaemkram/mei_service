/*
 * domain_response_server.c
 *
 *  Created on: May 22, 2019
 *      Author: Mark Meadows
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>

extern int procnumber;
extern char MEI_STATUS[30]; //GLOBAL STATUS OF THE MEI
extern char LAST_MEI_STATUS[30];
int txsock = -1;
char mei_response_sock_name[250] = {0};
extern int DEBUG_LOG;

void domain_response_server(void)
{
	   //printf("txsock = %d\n",txsock);//DEBUG
	    if(txsock <= 0 ){

		int sock;
		struct sockaddr_un server; //Set up structure for socket
		sock = socket(AF_UNIX, SOCK_STREAM, 0); //setup socket
		fcntl(sock, F_SETFL, O_NONBLOCK); // Set Socket for NON-Blocking
		server.sun_family = AF_UNIX;           //Protocol

		sprintf(mei_response_sock_name,"/var/run/mei_response%d.socket",procnumber);
		//strcpy(server.sun_path, "mei_response.sock");		//build socket path
		strcpy(server.sun_path,mei_response_sock_name);
		bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)); //Bind Socket

	    listen(sock, 1); //Listen to socket
	    usleep(100000);  //This delay is critical for the operation of the network client
		txsock = accept(sock, 0, 0); //Accept connection from anyone

		if (txsock <= 0)
		{
			//perror("socket"); //DEBUG should say Resource Temporarily Unavailable
			close(txsock);
			close(sock);
			unlink(mei_response_sock_name);
			return;
		}
	}

	if (DEBUG_LOG == 1 && txsock >= 0)
	{
		log_Function("Client Connected");
	}

	if (strcmp(MEI_STATUS,LAST_MEI_STATUS) != 0)
	{
	write(txsock,MEI_STATUS,strlen(MEI_STATUS));
	write(txsock,"\n",1);
	}
	return;

}
