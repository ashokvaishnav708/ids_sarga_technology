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
 **************************************************************************************

 @File          ST_PIR.c 
 
 @Description   This file includes the MC operation code to operate PIR Sensor
 				
 @author        Nawaj khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 ****************************************************************************************
 */

/*						Header File Inclusions
*****************************************************************************************/

#include <avr/io.h>
#include <st_pir.h>

/* Pull down Pin B0 */ 

int ids_read_pir()
{
	return ((PINC & (1<<PINC5))==0);
} 