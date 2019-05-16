/*
===================================================================================================================
Implementation of the MEI XOR Check Sum in ANSI C
===================================================================================================================
 */
int do_crc(char buff[], int buffer_len){

	 //printf("\n%02x%02x%02x%02x%02x%02x\n",buff[0],buff[1],buff[2],buff[3],buff[4],buff[5]);//DEBUG

	 //printf("%d\n",buffer_len);//DEBUG

	 int i=1;
	 unsigned int sum = 0;

	 buffer_len = buffer_len - 2;

	        while ( i < buffer_len)
	        {
	           sum ^= buff[i];
	           //printf("%02x,%02x\n",sum,buff[i]);//DEBUG
	           i++;
	        }
	        //printf("%d\n",buffer_len); //DEBUG
            //printf("the check sum = %02x\n",sum);//DEBUG

	 return(sum);
}
/*
============================================================================================================
ENd of Check Sum Function
============================================================================================================
 */


