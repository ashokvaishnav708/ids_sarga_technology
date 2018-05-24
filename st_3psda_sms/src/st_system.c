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

/***************************************************************************************

 @File			st_system.c 
 
 @Description   This file includes the MC operation code of beep generation and off.
                This also contains the functions to ON/OFF the system LED
 				
 @author        Nawaj khan <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *****************************************************************************************/

/******************Header File Inclusions*************************************************/


#include <avr/io.h>
#include <st_system.h>
#include <st_alarmsys.h>
#include <st_usart.h>
#include <st_delay.h>


/**************************************************************************

@Name	            ids_set_sys_led()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to ON and OFF the Status LED.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_set_sys_led(int stat)
{
	if (stat == ON)
	{
		PORTD |= (1<<PORTD6);

	}
	else if(stat == OFF)
	{
		PORTD &=~ (1<<PORTD6);
	}
}

/**************************************************************************

@Name	            ids_beep()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to ON and OFF the beep.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_beep()
{
	// Buzzer Notification
	PORTC |= (1<<PINC0);
	ids_delayms(1);
	PORTC &=~ (1<<PINC0);
}
