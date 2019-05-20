/*
 * domain_socket_server.c
 *
 *  Created on: May 14, 2019
 *      Author: mark
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#define NAME "mei_service.sock"
int RUNONCE = 0;

void domain_socket_server (void)
{


	int sock, msgsock, rval;
	struct sockaddr_un server;
	char buf[1024];

	if(RUNONCE == 0)
	{
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	//fcntl(socket_fd, F_SETFL, O_NONBLOCK); // Set Socket for NON-Blocking

	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, NAME);
	if (bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un))) {
		perror("binding stream socket");
		exit(1);
	 }

	printf("Socket Created name %s\n", server.sun_path);
	listen(sock, 5);


		msgsock = accept(sock, 0, 0);
		RUNONCE = 1;
	}

	fcntl(sock, F_SETFL, O_NONBLOCK); // Set Socket for NON-Blocking
		//if (msgsock == -1)
		//	perror("accept");
		//else do {
			bzero(buf, sizeof(buf));
			rval = read(msgsock, buf, 1024);
			//if ((rval = read(msgsock, buf, 1024)) < 0)
				//perror("reading stream message");
			//else if (rval == 0)

				//printf("Ending connection\n");
			//else
				printf("-->%s\n", buf);
		//} while (rval > 0);
		//close(msgsock);

	//close(sock);
	//unlink(NAME);

}







