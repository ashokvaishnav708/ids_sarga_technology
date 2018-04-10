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

/* Messages to be sent to owner when intruder detected*/
char sms1[] = {"Beware Sir/Madam! Be alert someone entering your showroom with criminal intent."}; // First message
char sms2[] = {"Hope Sir/Madam you took measures and arrived at your showroom to check intruder."}; // Second message
char sms3[] = {"Kindly switch off the alarm once you reach and check box, connections before restoring."}; // Third message
					
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


void ids_on_detect_stuff(char *num)
{
	/* Activate Communication & Alarm System */
	ids_raisealarm();
	// ASHOK START
	ids_transmit_call1(); // Call to OWNER1
	ids_delayms(350); // delay of 35 seconds
	ids_transmit_discon();
	ids_delayms(1);
	ids_transmit_call2(); // Call to OWNER2
	ids_delayms(350); // delay of 35 seconds
	ids_transmit_discon();
	ids_delayms(1);
	ids_send_sms(num, sms1); // send first sms
	ids_delayms(300); // delay of 30 seconds
	ids_send_sms(num, sms2); // send second sms
	ids_delayms(300); // delay of 30 seconds
	ids_send_sms(num, sms3); // send third sms
	ids_delayms(10);
	// ASHOK END
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

//ASHOK START
//function to send message
void ids_send_sms(char *number, char *message)
{
	for(int z=0;cmd4[z]!='\0';z++)
	{
		UDR=cmd4[z];
		ids_delayms(1);
	}
	ids_delayms(20);
	UDR = 10;
	
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
}

/* Select memory of Phonebook */
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