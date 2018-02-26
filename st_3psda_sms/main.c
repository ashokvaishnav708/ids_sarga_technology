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

 @File          main.c 
 
 @Description   This is the main file to control & operate whole system.  
				

 @author        Nawaj Khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************
 */

/*						Header File Inclusions
***************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <st_usart.h>
#include <util/delay.h>
#include <string.h>
#include <avr/eeprom.h>
#include <stdbool.h>

#include <st_msg.h>
#include <st_port.h>
#include <st_pir.h>
#include <st_mrs.h>
#include <st_alarmsys.h>
#include <st_system.h>
#include <st_delay.h>

int st=0; // for debugging double beep problem
int i=0; // used for USART interrupt status
char on_sms[] = {"Your security system is turned On."}; // message to acknowledge the ON status
char off_sms[] = {"Your security system is turned Off."}; // message to acknowledge the OFF status

/* Messages to be sent to owner when intruder detected*/
char sms1[] = {"Beware Sir/Madam! Be alert someone entering your showroom with criminal intent."}; // First message
char sms2[] = {"Hope Sir/Madam you took measures and arrived at your showroom to check intruder."}; // Second message
char sms3[] = {"Kindly switch off the alarm once you reach and check box, connections before restoring."}; // Third message

int s=0,j=0; // variables required while fetching owner number
int x=0,status=0; // used for USART interrupt status
char info[150],num[20]; // 'info' for USART buffer and 'num' for storing owner number
/* Flags for future purpose*/
volatile int remote_flag = 0;
volatile int active_flag = 0; 
volatile int system_flag = 0; 
volatile int int_flag = 0;


// ASHOK START
int ids_get_owner(void); // To get owner contact from SIM
void ids_on_stuff(void);

int ids_get_owner()
{
	int ret=0;
	s=0;
	j=0;
	x=0;
	status=0;
	ids_select_mem();
	x=0;
	status=0;
	ids_delayms(1);
	ids_req_owner();
	if(status==1)
	{
		for (int z=0;info[z]!='\0';z++)
		{
			if (info[z]=='"') s++;
			else if (s==3)
			{
				num[j]=info[z];
				j++;
			}
			else if (s==4) break;
		}
		if((strlen(num)==10)||strlen(num)==13)
		{
			ret=1;
		}
		else
		{
			ret=0;
		}
	}
	return ret;
}

void ids_on_stuff()
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
	x=0;
	ids_delayms(1);
	ids_send_sms(num, sms1); // send first sms
	x=0;
	ids_delayms(300); // delay of 30 seconds
	ids_send_sms(num, sms2); // send second sms
	x=0;
	ids_delayms(300); // delay of 30 seconds
	ids_send_sms(num, sms3); // send third sms
	ids_delayms(10);
	active_flag=1;
	x=0;
	status=0;
	// ASHOK END
}

/* ISR for USART*/
ISR(USART_RXC_vect)
{
	char temp;
	temp=UDR;
	if (temp!='\r'&&temp!='\n') // Removing Newline and Start character from USART buffer
	{
		info[x]=temp;
		x++;
	}
	status=1;
}

// ASHOK END

/* ISR for OFF Signal from Remote*/
ISR(INT0_vect)
{
	if (st==0)
	{
		st=1;
		ids_beep(); // beep buzzer once
	}
	system_flag = 0;
	int_flag=1;
	ids_system(OFF);
	ids_transmit_discon();
	eeprom_write_byte(000000,3); 
}
/* ISR for ON Signal from Remote*/
ISR(INT1_vect)
{
	if (st==0)
	{
		st=1;
		ids_beep();
	}
	system_flag = 1;
	int_flag=1;
	ids_system(ON);
	eeprom_write_byte(000000,2);
}


int main ()
{
	int owner;
	/* Port Initialization */
	ids_port_init();
	/* External Interrupt Initialization */
	ids_extint_init();
	/* USART Initialization */
	ids_usart_init();
	ids_delayms(30); // Delay until USART initializes completely
	/* Getting OWNER Number from SIM*/
	do 
	{
		ids_system(ON);
		owner=ids_get_owner(); // returns 1 if GOT owner number else 0
		ids_system(OFF);
	} while (owner!=1);
	
	x=0;
	status=0;
	/* Cleaning USART buffer */
	for (i=0;i<150;i++)
	{
		info[i]='\0';
	}
	/* Infinite Loop*/
	while (1)
	{
		if (ids_read_button())
		{
			ids_on_stuff();
		}
		if (eeprom_read_byte(000000)==2)
		{
			/* System is ON now */
			x=0;
			status=0;
			ids_delayms(5);
			st=0;
			/* Checking Sensors Indication */
			if (((ids_pir_1() == true)||(ids_mrs_read() == 0))) 
			{
				_delay_ms(500);
				if  (((ids_pir_1() == 0)||(ids_mrs_read() == 0))&&(active_flag==0))
				{
					ids_on_stuff();
				}
			}
		}
		else if(eeprom_read_byte(000000)==3)
		{
			/* System is OFF now */
			x=0;
			status=0;
			ids_delayms(5);
			st=0;
			active_flag=0;
		}
		
		/* check sms arrival for arming and disarming */
		//ASHOK START
		if (status==1)
		{
			if (strstr(info,"OWNER")!=NULL)
			{
				if (strstr(info,"ON")!=NULL)
				{
					/* SMS arrived for ON */
					ids_beep();
					ids_system(ON);
					eeprom_write_byte(000000,2);
					ids_send_sms(num, on_sms);
				}
				else if (strstr(info,"OFF")!=NULL)
				{
					/* SMS arrived for OFF */
					ids_beep();
					ids_system(OFF);
					eeprom_write_byte(000000,3);
					ids_send_sms(num ,off_sms);
				}
				/* Clean USART buffer */
				for (i=0;info[i]!='\0';i++)
				{
					info[i]='\0';
				}
				/* Reset USART variables */
				i=0;
				x=0;
				status=0;
			}
		}
		//ASHOK END
	}
	return 0;
}



