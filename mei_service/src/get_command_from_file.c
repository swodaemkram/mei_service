/*
 * get_command_from_file.c
 *
 *  Created on: May 15, 2019
 *      Author: mark
 */
#include <stdio.h>
char MEI_CURRENT_COMMAND[30] = "idle";

void get_command_from_file(void)
{

FILE *fp;
char buff[255];

fp = fopen("mei_command", "r");
fgets(buff,255,(FILE*)fp);

if(strlen(buff) <= 0)
{
	strcpy(MEI_CURRENT_COMMAND,buff); // We dont want to change the command to Blank if the file is empty
}
//printf("\nCommand is = %s\n",buff);
fclose(fp);
	return;
}
