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

 @File          ST_delay.c 
 
 @Description   This file includes the MC operation code of delay

 @author        Nawaj Khan <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************/

/*******************************Header File Inclusions*******************************/
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <st_delay.h>

/**************************************************************************

@Name	            ids_delayms
@Input_Parameter	Delay value
@Output_Parameter	None
@Description	    This function is used to provide delay in the execution
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_delayms(unsigned int t)
{
	unsigned int i;
	for(i=0;i<t;i++)
	_delay_ms(100); 
}