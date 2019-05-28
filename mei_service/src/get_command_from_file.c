/*
 * get_command_from_file.c
 *
 *  Created on: May 15, 2019
 *      Author: mark
 */
#include <stdio.h>
char MEI_CURRENT_COMMAND[30] = "idle";
char mei_command_file_name[250] = {0};
extern int procnumber;

void get_command_from_file(void)
{

FILE *fp;
char buff[255] = {0};

sprintf(mei_command_file_name,"mei_command%d",procnumber);

if (fopen(mei_command_file_name,"r")== NULL)
{
	fp = fopen(mei_command_file_name,"w");
	fclose(fp);
}

fp = fopen(mei_command_file_name,"r");
fgets(buff,255,(FILE*)fp);

if(strlen(buff) >= 1)
{
	strcpy(MEI_CURRENT_COMMAND,buff); // We dont want to change the command to Blank if the file is empty
}
//printf("\nCommand is = %s\n",buff);
fclose(fp);
return;
}
