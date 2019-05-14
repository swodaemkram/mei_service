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

/* Read text from the socket and print it out. Continue until the
   message, zero otherwise.  */

void server (int client_socket)
{

	 int length;
     char* text;

     /* First, read the length of the text message from the socket. If
        read returns zero, the client closed the connection.  */

     if (read (client_socket, &length, sizeof (length)) == 0)

     /* Allocate a buffer to hold the text.  */

     text = (char*) malloc (length);

     /* Read the text itself, and print it.  */

     read (client_socket, text, length);
     printf ("%s\n", text);

     /* Free the buffer.  */

     free (text);

     return;

   }







