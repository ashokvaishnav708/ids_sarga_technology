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

 @File          ST_Port.h 
 
 @Description   This file includes the UART code to operate GSM Module.

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************/

#ifndef PORTINIT_H_
#define PORTINIT_H_

/****Function Prototype***********/

void ids_port_init(void);

void ids_extint_init(void);

int ids_panic_btn_status(void);

#endif /* PORTINIT_H_ */
