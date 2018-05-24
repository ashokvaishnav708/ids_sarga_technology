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

 @File          ST_USART.h 
 
 @Description   This file has header file to Initiate Transmission & Reception
				with GSM Module

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************/




#ifndef USART_H_
#define USART_H_

#define F_CPU 8000000UL /* Specifies the CPU frequency */
#define BAUDRATE 9600	/* Baud rate declaration */		
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)	/* Calculate UBRR value */	
	
								
/********Function Prototype************/

void ids_usart_init(void);

void ids_extract_cnum(void);

void ids_call_owner(int);

void ids_disconn_call(void);

void ids_mem_type(void);

void ids_send_sms(char *, char *);

void ids_sel_sms_mode(void);

void ids_free_uart(void);

void ids_attention(void);

#endif /* USART_H_ */