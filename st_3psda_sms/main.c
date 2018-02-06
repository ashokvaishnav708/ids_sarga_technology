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
int i=0,x=0,status=0;
char on_sms[] = {"Your security system is turned On."};
char off_sms[] = {"Your security system is turned Off."};
char sms1[] = {"Alert! Intruders Detected in your premises."};
char sms2[] = {"Kindly take appropriate action."};
char sms3[] = {"Hope you have taken necessary action."};

volatile int remote_flag = 0;
volatile int active_flag = 0; 
volatile int system_flag = 0; 
volatile int int_flag = 0;


// ASHOK START
int get_owner(void);

int get_owner()
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
			ret=1;
		}
		else
		{
			ret=0;
		}
	}
	return ret;
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

// ASHOK END

ISR(INT0_vect)
{
	if (st==0)
	{
		st=1;
		ids_beep();
	}
	system_flag = 0;
	int_flag=1;
	ids_system(OFF);
	eeprom_write_byte(000000,3);
}
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
	ids_delayms(30);
	
	do 
	{
		ids_system(ON);
		owner=get_owner();
		ids_system(OFF);
	} while (owner!=1);
	x=0;
	status=0;
	for (i=0;i<150;i++)
	{
		info[i]='\0';
	}
	while (1)
	{
		if (eeprom_read_byte(000000)==2)
		{
			x=0;
			status=0;
			ids_delayms(5);
			st=0;
			if (((ids_pir_1() == true)||(ids_mrs_read() == 0)))
			{
				_delay_ms(500);
				if  (((ids_pir_1() == 0)||(ids_mrs_read() == 0))&&(active_flag==0))
				{
					/* Activate Communication & Alarm System */
					ids_raisealarm();
					// ASHOK START
					ids_transmit_call1();
					ids_delayms(350);
					ids_transmit_discon();
					ids_delayms(1);
					ids_transmit_call2();
					ids_delayms(350);
					ids_transmit_discon();
					x=0;
					ids_delayms(1);
					ids_send_sms(num, sms1);
					x=0;
					ids_delayms(300);
					ids_send_sms(num, sms2);
					x=0;
					ids_delayms(300);
					ids_send_sms(num, sms3);
					ids_delayms(10);
					active_flag=1;
					x=0;
					status=0;
					// ASHOK END
				}
			}
		}
		else if(eeprom_read_byte(000000)==3)
		{
			x=0;
			status=0;
			ids_delayms(5);
			st=0;
			active_flag=0;
		}
		//ASHOK START
		if (status==1)
		{
			if (strstr(info,"OWNER")!=NULL)
			{
				if (strstr(info,"ON")!=NULL)
				{
					ids_beep();
					ids_system(ON);
					eeprom_write_byte(000000,2);
					ids_send_sms(num, on_sms);
				}
				else if (strstr(info,"OFF")!=NULL)
				{
					ids_beep();
					ids_system(OFF);
					eeprom_write_byte(000000,3);
					ids_send_sms(num ,off_sms);
				}
				for (i=0;info[i]!='\0';i++)
				{
					info[i]='\0';
				}
				i=0;
				x=0;
				status=0;
			}
		}
		//ASHOK END
	}
	return 0;
}



