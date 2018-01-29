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

 @File          ST_MSG.c 
 
 @Description   This file includes the MC operation code to operate Sensors
				& Generate Call & SMS

 @author        Nawaj Khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *************************************************************************************
 */

/*								Header File Inclusions
**************************************************************************************/

#include <avr/io.h>
#include <st_msg.h>
#include <st_alarmsys.h>
#include <st_usart.h>

/* Activation of Alarm & Call System */

void ids_raisealarm()
{
	/* Activate Alarm System */
	ids_siren(ON);
	/* Call to Owners */
	ids_transmit_call();

}