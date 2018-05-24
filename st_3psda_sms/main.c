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

 @File          main.c 
 
 @Description   This is the main file to control & operate whole system.  
				

 @author        Nawaj Khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************/

/*****************Header File Inclusions***********************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <st_usart.h>
#include <util/delay.h>
#include <string.h>
#include <avr/eeprom.h>
#include <stdbool.h>

#include <st_port.h>
#include <st_pir.h>
#include <st_mrs.h>
#include <st_alarmsys.h>
#include <st_system.h>
#include <st_delay.h>

/*Global Variable Declaration*/

int st=0;                                                  // for debugging double beep problem
int i=0;                                                   // index variable for UART buffer
char on_sms[] = {"Your security system is turned On."};    // message to acknowledge the ON status
char off_sms[] = {"Your security system is turned Off."};  // message to acknowledge the OFF status
int s=0,j=0;                                               // variables required while fetching owner number
int x=0,status=0;                                          // used for USART interrupt status
char info[150];											   // 'info' for USART buffer
static char number[20];                                    // 'number' for storing owner number
volatile int active_flag = 0;


/* Messages to be sent to owner when intruder detected*/
char sms1[] = {"Beware Sir/Madam! Be alert someone entering your showroom with criminal intent."}; // First message
char sms2[] = {"Hope Sir/Madam you took measures and arrived at your showroom to check intruder."}; // Second message
char sms3[] = {"Kindly switch off the alarm once you reach and check box and connections before restoring."}; // Third message



/* Functions Prototype Declaration */
void ids_alert_system(void);
int ids_retrv_owner_num(void);  // To get owner contact from SIM
void ids_cln_ubf(void);        // Reset USART variables
void ids_system_arm(void);
void ids_system_disarm(void);
void ids_init(void);
void ids_read_sensors(void);
void ids_check_sms(void);



/**************************************************************************

@Name	            ISR
@Input_Parameter	USART_RXC_vect
@Output_Parameter	None
@Description	    This function is the interrupt service routine to cater 
                    interrupt from USART, it will deliver data from GSM.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
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

/**************************************************************************

@Name	            ISR
@Input_Parameter	INT0_vect
@Output_Parameter	None
@Description	    This function is the interrupt service routine to cater 
                    interrupt from remote, it will disarm the system.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
ISR(INT0_vect)
{
	ids_system_disarm();
}


/**************************************************************************

@Name	            ISR
@Input_Parameter	INT1_vect
@Output_Parameter	None
@Description	    This function is the interrupt service routine to cater 
                    interrupt from remote, it will arm the system.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
ISR(INT1_vect)
{
	ids_system_arm();
}


/*****************************************************************

@Name	ids_system_arm
@Input_Parameter	None
@Output_Parameter	None
@Description	This function is to arm the system.
On execution of the function the system will check sensors status.
@Owner	ASHOK VAISHNAV

*****************************************************************/
void ids_system_arm()
{
	if (st==0)
	{
		st=1;
		ids_beep();
	}
	ids_set_sys_led(ON);
	eeprom_write_byte(000000,2);
}

/***************************************************************************************

@Name	ids_system_disarm
@Input_Parameter	None
@Output_Parameter	None
@Description	This function is to disarm the system. 
				On execution of the function the system will not check sensors status.
@Owner	ASHOK VAISHNAV

****************************************************************************************/
void ids_system_disarm()
{
	if (st==0)
	{
		st=1;
		ids_beep(); // beep buzzer once
	}
	ids_set_sys_led(OFF); //ids_set_sys_state()
	ids_siren_disable();
	ids_disconn_call();
	active_flag=0;
	eeprom_write_byte(000000,3);
}


/*********************************************************************************

@Name	ids_check_sms
@Input_Parameter	None
@Output_Parameter	None
@Description	This function checks the arrival of message. 
				Validate the arrived message whether the system has to ON or OFF.
				Change the system state accordingly.
@Owner	ASHOK VAISHNAV

*********************************************************************************/
void ids_check_sms()
{
	if (status==1)
	{
		if (strstr(info,"OWNER")!=NULL)
		{
			if (strstr(info,"ON")!=NULL)
			{
				/* SMS arrived for ON */
				ids_beep();
				ids_set_sys_led(ON);
				eeprom_write_byte(000000,2);
				active_flag=0;
				ids_send_sms(number, on_sms);
			}
			else if (strstr(info,"OFF")!=NULL)
			{
				/* SMS arrived for OFF */
				ids_beep();
				ids_set_sys_led(OFF);
				eeprom_write_byte(000000,3);
				active_flag=0;
				ids_send_sms(number ,off_sms);
			}
			ids_cln_ubf();
		}
	}
}


/**********************************************************************

@Name	ids_alert_system
@Input_Parameter	None
@Output_Parameter	None
@Description	This function starts when an Intruder is detected.
It starts loud buzzer and call and SMS to OWNERS.
@Owner	ASHOK VAISHNAV

************************************************************************/
void ids_alert_system() //ids_start
{
	active_flag=1;
	/* Activate Communication & Alarm System */
	ids_siren_enable();
	ids_delayms(10);
	/* Calling Owner 1 */
	ids_call_owner(1); 
	ids_delayms(350); 
	if ( active_flag == 1)
	{
		/* Calling Owner 2 */
		ids_disconn_call();  
		ids_delayms(10);
		ids_call_owner(2); 
		ids_delayms(350); 
		if ( active_flag == 1 )
		{
			/* Sending First Message to Owner */
			ids_disconn_call();
			ids_cln_ubf();
			ids_delayms(1);
			ids_attention();
			ids_delayms(10);
			ids_send_sms(number, sms1); 
			ids_cln_ubf();
			ids_delayms(300); 
			if ( active_flag == 1 )
			{
				/* Sending Second Message to Owner */
				ids_attention();
				ids_delayms(10);
				ids_send_sms(number, sms2);
				ids_cln_ubf();
				ids_delayms(300); 
				if ( active_flag == 1 )
				{
					/* Sending Third Message to Owner */
					ids_attention();
					ids_delayms(10);
					ids_send_sms(number, sms3);
					ids_cln_ubf();
					ids_delayms(10);
				}
			}
		}
	}
	ids_cln_ubf();
}

/****************************************************************************************

@Name	ids_read_sensors
@Input_Parameter	None
@Output_Parameter	None
@Description	This function checks the sensors and panic button status. 
				If sensor or sensor detects the intruder then system goes to alert mode.
@Owner	ASHOK VAISHNAV

****************************************************************************************/

void ids_read_sensors()
{
	if (ids_panic_btn_status()) //ids_panic_btn_status()
	{
		ids_alert_system();
		ids_cln_ubf();
	}
	if (eeprom_read_byte(000000)==2)
	{
		/* System is ON now */
		x=0;
		status=0;
		active_flag=0;
		ids_delayms(5);
		st=0;
		/* Checking Sensors Indication */
		if (((ids_read_pir() == 0)||(ids_mrs_read() == 0)))
		{
			_delay_ms(500);
			if  (((ids_read_pir() == 0)||(ids_mrs_read() == 0))&&(active_flag==0))
			{
				ids_alert_system();
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
	}
}

/********************************************************************************

@Name	ids_init
@Input_Parameter	None
@Output_Parameter	None
@Description	This function executes when system has started. 
				It initializes the overall system and make it ready to be used.
@Owner	ASHOK VAISHNAV

*********************************************************************************/

void ids_init()
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
		//ids_delayms(5);
		ids_set_sys_led(ON);
		owner = ids_retrv_owner_num(); // returns 1 if GOT owner number else 0
		ids_set_sys_led(OFF);
	} while (owner != 1);
	owner=0;
	ids_cln_ubf();
	eeprom_write_byte(000000,3);
}


/******************************************************************************

@Name	ids_retrv_owner_num
@Input_Parameter	None
@Output_Parameter	return 0 or 1
@Description	This function retrieves the owner contact number from SIM card.
@Owner	ASHOK VAISHNAV

******************************************************************************/
int ids_retrv_owner_num()
{
	int ret=0;
	s=0;
	j=0;
	ids_cln_ubf();       //ids_cln_ubuf
	ids_mem_type();     //ids_mem_type()
	ids_cln_ubf();
	ids_delayms(1);
	ids_extract_cnum(); //ids_extract_cnum
	if(status==1) //if possible put this code in a separate function
	{
		/* Owner Contact Number extraction Code */
		for (int z=0;info[z]!='\0';z++)
		{
			if (info[z]=='"') s++;
			else if (s==3)
			{
				number[j]=info[z];
				j++;
			}
			else if (s==4) break;
		}
		if((strlen(number)==10)||strlen(number)==13)
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

/**************************************************************************

@Name	ids_cln_ubuf
@Input_Parameter	None
@Output_Parameter	None
@Description	This function cleans the USART buffer and its index values.
@Owner	ASHOK VAISHNAV

**************************************************************************/

void ids_cln_ubf()
{
	/* Clean USART buffer */
	for (i=0;info[i]!='\0';i++)
	{
		info[i]='\0';
	}
	/* Reset USART variables */
	x=0;
	status=0;
}


/**********************************************************************

@Name	            main()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This is the entry point of the system
@Owner	ASHOK VAISHNAV

************************************************************************/

int main ()
{
	ids_init(); // System Initialize
	while (1) //Infinite Loop
	{
		ids_read_sensors(); // Checks sensors status
		ids_check_sms(); // Checks the SMS for system ON or OFF
		ids_cln_ubf();
	}
	return 0;
}



