/**************************************************************************************
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
***************************************************************************************/

/**************************************************************************************

 @File          ST_USART.c 
 
 @Description   This file includes the MC operation code of USART to Initialization 
				Transmission & Reception with GSM Module

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************/

/************************Header File Inclusions****************************************/

#include <avr/io.h>
#include <st_usart.h>
#include <st_delay.h>
#include <util/delay.h>
#include <string.h>

#define ON  1
#define OFF 0
#define BAUDRATE 9600                               /* Baud rate declaration */
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)			/* Calculate UBRR value */
				
					
/********Commands for GSM Call & SMS ***********************/

unsigned char cmd[5] = {"AT\r"};
unsigned char cmd0[20] = {"ATD>\"OWNER2\";\r"};
unsigned char cmd1[20] = {"ATD>\"OWNER\";\r"};
unsigned char cmd2[10] = {"ATH\r"};
unsigned char cmdSM[15] = {"AT+CPBS=\"SM\""};
unsigned char cmd3[25] = {"AT+CPBF=\"OWNER\";\r"};
unsigned char cmd4[10] = {"AT+CMGF=1"};
char cmd5[30] = {"AT+CMGS=\""};


/**************************************************************************

@Name	            ids_usart_init()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to initialize USART.
@Owner	            ASHOK VAISHNAV

**************************************************************************/	
void ids_usart_init()
{
	UBRRL=(uint8_t)UBRRVAL;												
	UBRRH=(UBRRVAL>>8);													
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UCSRB|=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
} 


/**************************************************************************

@Name	            ids_free_uart()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to clean the previous input to UART.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_free_uart()
{
	while((UCSRA &(1<<UDRE)) == 0);
}



/**************************************************************************

@Name	            ids_attention()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to reset the state of GSM.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_attention()
{
	for(int z=0;cmd[z]!='\0';z++)
	{
		ids_free_uart();
		UDR = cmd[z];
		ids_delayms(1);
	}
	//UDR = 13;
	ids_free_uart();
	UDR = 10;
}


/**************************************************************************

@Name	            ids_call_owner()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to initiate call to the number 
                    stored with name of owner.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_call_owner(int ownr)
{
	if (ownr==1)
	{
		for(int z=0;cmd1[z]!='\0';z++)
		{
			/* Call OWNER1 */
			ids_free_uart();
			UDR = cmd1[z];
			ids_delayms(1);
		}
	}
	else if(ownr==2)
	{	
		for(int z=0;cmd0[z]!='\0';z++)
		{
			ids_free_uart();
			/* OWNER2 call */
			UDR = cmd0[z];
			ids_delayms(1);
		}
	}
	ids_delayms(40);
	ids_free_uart();
	UDR = 10;
	
}

/**************************************************************************

@Name	            ids_disconn_call()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to disconnect the ongoing call.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
/* Send Command 2 */
void ids_disconn_call()
{
	for(int z=0;cmd2[z]!='\0';z++)
	{	
		ids_free_uart();
		UDR = cmd2[z];
		ids_delayms(1);
	}
	//UDR = 13;
	ids_free_uart();
	UDR = 10;
}
/**************************************************************************

@Name	            ids_sel_sms_mode()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to select the SMS mode in GSM
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_sel_sms_mode()
{
	for(int z=0;cmd4[z]!='\0';z++)
	{
		ids_free_uart();
		UDR=cmd4[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	ids_free_uart();
	UDR = 10;
}


/*********************************************************************************

@Name	            ids_send_sms()
@Input_Parameter	char *number, char *message
@Output_Parameter	None
@Description	    This function is used to send the SMS to the register number
@Owner	            ASHOK VAISHNAV

*********************************************************************************/
void ids_send_sms(char *number, char *message)
{	
	strcat(cmd5, number);
	strcat(cmd5, "\"\r");
	ids_delayms(1);
	
	for(int z=0;cmd5[z]!='\0';z++)
	{
		ids_free_uart();
		UDR=cmd5[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	ids_free_uart();
	UDR = 10;
		
	ids_delayms(1);
	
	for(int z=0;message[z]!='\0';z++)
	{
		ids_free_uart();
		UDR=message[z];
		ids_delayms(1);
	}
	ids_free_uart();
	UDR = 26;
	ids_delayms(20);
	ids_free_uart();
	UDR = 10;
	strcpy(cmd5,"AT+CMGS=\"");
}
/**************************************************************************

@Name	            ids_mem_type()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to select the memory type of 
                    mobile from where number has to be retrieved.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_mem_type()
{
	for(int z=0;cmdSM[z]!='\0';z++)
	{
		ids_free_uart();
		UDR=cmdSM[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	ids_free_uart();
	UDR = 10;
}
/**************************************************************************

@Name	            ids_extract_cnum()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to extract the contact number from SIM
@Owner	            ASHOK VAISHNAV

**************************************************************************/

void ids_extract_cnum()
{
	for(int z=0;cmd3[z]!='\0';z++)
	{
		ids_free_uart();
		UDR=cmd3[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	ids_free_uart();
	UDR = 10;
}


