/*
*************************************************************************************
*
*									SARGA TECHNOLOGY
*
*							 Intruders Detection System IC Code
*
*						This code is the property of Sarga Technology.
*				 (C) Copyright Sarga Technology 2015. All Rights Reserved.
*
*	S A R G A  T E C H N O L O G Y   C O N F I D E N T I A L   P R O P R I E T A R Y
*
*
*
**************************************************************************************
*/


/*!
 *************************************************************************************

 @File          ST_USART.c 
 
 @Description   This file includes the MC operation code of USART to Initialization 
				Transmission & Reception with GSM Module

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *************************************************************************************
 */

/*						Header File Inclusions
**************************************************************************************/

#include <avr/io.h>
#include <st_usart.h>
#include <st_delay.h>
#include <util/delay.h>
#include <string.h>
#include <st_msg.h>

#define ON 1
#define OFF 0
/* Calculate UBRR value */
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)			
/* Baud rate declaration */				
#define BAUDRATE 9600												



int terminate=0;
					
//ASHOK START
unsigned char cmd0[] = {"ATD>\"OWNER2\";\r"};
unsigned char cmd1[] = {"ATD>\"OWNER\";\r"};
unsigned char cmd2[] = {"ATH\r"};
unsigned char cmdSM[] = {"AT+CPBS=\"SM\""};
unsigned char cmd3[] = {"AT+CPBF=\"OWNER\";\r"};
unsigned char cmd4[] = {"AT+CMGF=1"};
char cmd5[] = {"AT+CMGS=\""};

//ASHOK END
									
/* Transmission & reception Initialization */						
void ids_usart_init()
{
	UBRRL=(uint8_t)UBRRVAL;												
	UBRRH=(UBRRVAL>>8);													
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UCSRB|=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
} 


/* Send Command 1 */
void ids_transmit_call1()
{
	for(int z=0;cmd1[z]!='\0';z++)
	{
		/* Put cmd5 into buffer, sends the cmd4 */
		UDR = cmd1[z];
		ids_delayms(1);
	}
	//UDR = 13;
	ids_delayms(40);
	UDR = 10;
}

//ASHOK START
void ids_transmit_call2()
{
	for(int z=0;cmd0[z]!='\0';z++)
	{
		/* Put cmd5 into buffer, sends the cmd4 */
		UDR = cmd0[z];
		ids_delayms(1);
	}
	//UDR = 13;
	ids_delayms(40);
	UDR = 10;
	
}
//ASHOK END

/* Send Command 2 */
void ids_transmit_discon()
{
	for(int z=0;cmd2[z]!='\0';z++)
	{	
		UDR = cmd2[z];
		ids_delayms(1);
	}
	//UDR = 13;
	UDR = 10;
}

void ids_sms_txtmd()
{
	for(int z=0;cmd4[z]!='\0';z++)
	{
		UDR=cmd4[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	UDR = 10;
}

//ASHOK START
//functions to send message

void ids_send_sms(char *number, char *message)
{	
	strcat(cmd5, number);
	strcat(cmd5, "\"\r");
	ids_delayms(1);
	
	for(int z=0;cmd5[z]!='\0';z++)
	{
		UDR=cmd5[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	UDR = 10;
		
	ids_delayms(1);
	
	for(int z=0;message[z]!='\0';z++)
	{
		UDR=message[z];
		ids_delayms(1);
	}
	UDR = 26;
	ids_delayms(20);
	UDR = 10;
	
	for (int z=0;cmd5[z]!='\0';z++)
	{
		cmd5[z]='\0';
	}
	strcpy(cmd5,"AT+CMGS=\"");
}

/* Select memory of Phone book */
void ids_select_mem()
{
	for(int z=0;cmdSM[z]!='\0';z++)
	{
		UDR=cmdSM[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	UDR = 10;
}

//Request for OWNER contact
void ids_req_owner()
{
	for(int z=0;cmd3[z]!='\0';z++)
	{
		UDR=cmd3[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	UDR = 10;
}



//ASHOK END