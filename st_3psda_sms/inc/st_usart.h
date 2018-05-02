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

 @File          ST_USART.h 
 
 @Description   This file has header file to Initiate Transmission & Reception
				with GSM Module

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *************************************************************************************
 */




#ifndef USART_H_
#define USART_H_
/* Specifies the CPU frequency */
#define F_CPU 8000000UL
/* Calculate UBRR value */
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)		
/* Baud rate declaration */		
#define BAUDRATE 9600												


void ids_usart_init(void);
void ids_req_owner();
void ids_transmit_call1();
void ids_transmit_call2();
void ids_transmit_discon();
void ids_transmit_ack(int stat);
void USART_Transmit( unsigned char data );
void ids_select_mem(void);
void ids_send_sms(char *, char *);
void ids_sms_txtmd(void);

#endif /* USART_H_ */