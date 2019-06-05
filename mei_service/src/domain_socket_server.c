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

	sprintf(mei_command_sock_name,"/var/run/mei_command%d.socket",procnumber);
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
		unlink(mei_command_sock_name);
		return;
	}

	//printf("msgsock = %d\n",msgsock);//debug
    bzero(buf, sizeof(buf));      //Zero out buffer
    rval = read(msgsock, buf, 1024); //Read from the socket
    //rval = recv(msgsock,buf,1024,0);   // Recv from socket same as ^

    if(rval > 0 )
	{
	//printf("--> %s\n ", buf); //Print Results DEBUG
	log_Function("client connected to send command");

if(strncmp(buf,"reset",5)==0 || strncmp(buf,"verify",6) ==0 || strncmp(buf,"stack",5) ==0 || strncmp(buf,"idle",4) ==0 || strncmp(buf,"appver",6)==0 ||
 strncmp(buf,"bootver",7)==0 || strncmp(buf,"model",5) ==0 || strncmp(buf,"serial",6) == 0 || strncmp(buf,"varname",7)==0|| strncmp(buf,"stop",4)==0)

    {
	strcpy(MEI_CURRENT_COMMAND,buf);
    }

    log_Function("client sent invalid command");
    close(msgsock);
    close(sock);
    unlink(mei_command_sock_name);
	return;
	}

    return;

}







