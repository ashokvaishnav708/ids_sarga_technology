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

char info[150],num[20];
char Temp;
int s=0,j=0;
int st=0;
unsigned int i=0,x=0,status=0;
char on_sms[] = {"Your security system is turned ON."};
char off_sms[] = {"Your security system is turned OFF."};
char detect_sms[] = {"Intrudors Detected at your site."};

volatile int remote_flag = 0;
volatile int active_flag = 0; 
volatile int system_flag = 0; 
volatile int int_flag = 0;

void send_sms(char *);

void send_sms(char *sms)
{
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
		for (i=0;info[i]!='\0';i++)
		{
			if (info[i]=='"') s++;
			else if (s==3)
			{
				num[j]=info[i];
				j++;
			}
			else if (s==4) break;
		}
		if((strlen(num)==10)||strlen(num)==13)
		{
			x=0;
			ids_send_sms(num, sms);
		}
	}
}

ISR(USART_RXC_vect)
{
	char temp;
	temp=UDR;
	if (temp!='\r'&&temp!='\n')
	{
		info[x]=temp;
		x++;
	}
	status=1;
}

ISR(INT0_vect)
{
	system_flag = 0;
	ids_beep();
	int_flag=1;
	ids_system(OFF);
	eeprom_write_byte(000000,3);
}
ISR(INT1_vect)
{
	system_flag = 1;
	ids_beep();
	int_flag=1;
	ids_system(ON);
	eeprom_write_byte(000000,2);
}


int main ()
{
	/* Port Initialization */
	ids_port_init();
	/* External Interrupt Initialization */
	ids_extint_init();
	/* USART Initialization */
	ids_usart_init();
	
	for (j=0;j<150;j++)
	{
		info[j] = '\0';
	}
	x=0;
	status=0;
	while (1)
	{	
		if (eeprom_read_byte(000000)==2)
		{
			//ids_system(ON);
			if (((ids_pir_1() == true)||(ids_mrs_read() == 0)))
			{
				_delay_ms(500);
				if  (((ids_pir_1() == 0)||(ids_mrs_read() == 0))&&(active_flag==0))
				{
					/* Activate Communication & Alarm System */	
					ids_raisealarm();
					ids_transmit_call1();
					ids_delayms(400);
					ids_transmit_discon();
					ids_delayms(1);
					ids_transmit_call2();
					active_flag=1;
					ids_delayms(20);
					send_sms(detect_sms);
					for (int j=0;info[j]!='\0';j++)
					{
						info[j] = '\0';
					}
				}
			}
		}
		else if(eeprom_read_byte(000000)==3)
		{
			//ids_system(OFF);
			active_flag=0;
		}
		if (status==1)
		{
			if (strstr(info,"OWNER")!=NULL)
			{		
				if (strstr(info,"ON")!=NULL)
				{
					ids_beep();
					ids_system(ON);
					eeprom_write_byte(000000,2);
					send_sms(on_sms);
				}
				if (strstr(info,"OFF")!=NULL)
				{
					ids_beep();
					ids_system(OFF);
					eeprom_write_byte(000000,3);
					send_sms(off_sms);
				}
				x=0;
				status=0;
				for (int j=0;info[j]!='\0';j++)
				{
					info[j] = '\0';
				}
			}
			x=0;
			status=0;
		}		
	}
	return 0;
}



