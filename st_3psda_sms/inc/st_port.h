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

 @File          ST_Port.h 
 
 @Description   This file includes the UART code to operate GSM Module.

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *************************************************************************************
 */

#ifndef PORTINIT_H_
#define PORTINIT_H_

/*

@Name	ids_port_init
@Input_Parameter	None
@Output_Parameter	None
@Description	This function enables all the available ports.
				It also assigns the data direction to the pins accordingly.
@Owner	NAWAZ KHAN

*/
void ids_port_init(void);

/*

@Name	ids_set_sys_led
@Input_Parameter	None
@Output_Parameter	None
@Description	This function enables the external interrupts to be accepted.
@Owner	NAWAZ KHAN

*/
void ids_extint_init(void);

/*

@Name	ids_panic_btn_status
@Input_Parameter	None
@Output_Parameter	flag
@Description	This function checks the panic button status.
				It returns true or false i.e. 0 or 1.
				Returns 1 if button pressed else 0.
@Owner	ASHOK VAISHNAV

*/
int ids_panic_btn_status(void);

#endif /* PORTINIT_H_ */
