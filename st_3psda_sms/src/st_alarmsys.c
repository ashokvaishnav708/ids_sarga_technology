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

 @File          ST_AlarmSys.c 
 
 @Description   This file includes the MC operation code to operate Alarm
				System

 @author        Nawaj Khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 ***********************************************************************************
 */

/*						Header File Inclusions
***********************************************************************************/
#include <avr/io.h>
#include <st_alarmsys.h>

/* Alarm System Initialization */


void ids_siren_enable()
{
	PORTB |= (1<<PINB1);
}

void ids_siren_disable()
{
	PORTB &=~ (1<<PINB1);
}
