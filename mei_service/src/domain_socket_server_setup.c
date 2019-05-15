/*
 * domain_socket_server_setup.c
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

void domain_socket_server_setup (void)

{
    const char* const socket_name = "mei_service_socket";
    int socket_fd;
    struct sockaddr_un name;
    int client_sent_quit_message;

    /* Create the socket.   */
    socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
    /* Indicate that this is a server.   */
    name.sun_family = AF_LOCAL;
    strcpy (name.sun_path, socket_name);
    bind (socket_fd, &name, SUN_LEN (&name));
    /* Listen for connections.   */
    listen (socket_fd, 5);

    /* Repeatedly accept connections, spinning off one server() to deal
       with  each  client.  Continue  until  a  client  sends  a  "quit"  message.   */
   // do {
      struct sockaddr_un client_name;
      socklen_t client_name_len;
      int client_socket_fd;

      /* Accept a connection.   */
      client_socket_fd = accept (socket_fd, &client_name, &client_name_len);
      /* Handle the connection.   */
      //client_sent_quit_message = server (client_socket_fd);
      /* Close our end of the connection.   */
      //close (client_socket_fd);

    //}

    //while (!client_sent_quit_message);

    /* Remove the socket file.   */

    //close (socket_fd);
    //unlink (socket_name);
 return;
}
