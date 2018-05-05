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

 @File          ST_AlarmSys.h
 
 @Description   This file header file of controlling Alarm System 

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *************************************************************************************
 */


#ifndef  ST_AlarmSys_H_
#define  ST_AlarmSys_H_

#define ON 1
#define OFF 0


/*

@Name	ids_siren_enable
@Input_Parameter	None
@Output_Parameter	None
@Description	This function simply starts the LOUD Buzzer alarm. 
@Owner	ASHOK VAISHNAV

*/
void ids_siren_enable(void);

/*

@Name	ids_siren_disable
@Input_Parameter	None
@Output_Parameter	None
@Description	This function simply stops the LOUD Buzzer alarm. 
@Owner	ASHOK VAISHNAV

*/
void ids_siren_disable(void);


#endif  /* ST_AlarmSys_H_ */