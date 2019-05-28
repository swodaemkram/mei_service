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
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>

extern char MEI_CURRENT_COMMAND[30] ;
extern int procnumber;
char mei_command_sock_name[250] = {0};

void domain_socket_server (void)
{

	int sock, msgsock, rval;
	struct sockaddr_un server; //Set up structure for socket
	char buf[1024];				//Buffer

	sock = socket(AF_UNIX, SOCK_STREAM, 0); //setup socket
	fcntl(sock, F_SETFL, O_NONBLOCK); // Set Socket for NON-Blocking
	server.sun_family = AF_UNIX;           //Protocol

	sprintf(mei_command_sock_name,"mei_command_%d.sock",procnumber);
	//strcpy(server.sun_path, "mei_command.sock");		//build socket path
	strcpy(server.sun_path, mei_command_sock_name);
	bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)); //Bind Socket

    listen(sock, 1); //Listen to socket
    usleep(100000);  //This delay is critical for the operation of the network client
	msgsock = accept(sock, 0, 0); //Accept connection from anyone

	if (msgsock == -1)
	{
		//perror("socket"); //DEBUG should say Resource Temporarily Unavailable
		close(msgsock);
		close(sock);
		unlink("mei_command.sock");
		//printf("BAIL\n");
		return;
	}

	//printf("msgsock = %d\n",msgsock);//debug
    bzero(buf, sizeof(buf));      //Zero out buffer
    rval = read(msgsock, buf, 1024); //Read from the socket
    //rval = recv(msgsock,buf,1024,0);   // Recv from socket same as ^

    if(rval > 0 )
	{
	//printf("--> %s\n ", buf); //Print Results DEBUG
	strcpy(MEI_CURRENT_COMMAND,buf);
	close(msgsock);
    close(sock);
    unlink("mei_command.sock");
	return;
	}

    return;

}







