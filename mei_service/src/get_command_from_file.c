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
strcpy(MEI_CURRENT_COMMAND,buff);
//printf("\nCommand is = %s\n",buff);
fclose(fp);
	return;
}
