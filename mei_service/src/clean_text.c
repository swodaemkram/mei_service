/*
 * clean_text.c
 *
 *  Created on: May 15, 2019
 *      Author: mark
 */

char * clean_text(char *text, int len_text)

{
	char clean_text[30] = {0};
	int i = 0;
	int a = 0;

	while (i<len_text)
	{
		if (text[i] >= 48 && text[i]<=121)
		{
			clean_text[a]=text[i];
			a++;
		}

		i++;
	}

	printf("Clean Text =%s \n",clean_text);

	return clean_text;
}
