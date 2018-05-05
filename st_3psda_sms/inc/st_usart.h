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

/*

@Name	ids_usart_init
@Input_Parameter	None
@Output_Parameter	None
@Description	It initializes and sets the USART parameters which are required for USART communication.
@Owner	NAWAZ KHAN

*/
void ids_usart_init(void);

/*

@Name	ids_extract_cnum
@Input_Parameter	None
@Output_Parameter	None
@Description	This function extracts the contact number of the OWNER.
@Owner	ASHOK VAISHNAV

*/
void ids_extract_cnum(void);

/*

@Name	ids_call_owner
@Input_Parameter	ownr
@Output_Parameter	None
@Description	This function calls the OWNER1 and OWNER2. 
				Selecting the owner is dependent on the input parameter.
@Owner	ASHOK VAISHNAV

*/
void ids_call_owner(int);

/*

@Name	ids_disconn_call
@Input_Parameter	None
@Output_Parameter	None
@Description	This function disconnects the call, currently in calling state. 
@Owner	ASHOK VAISHNAV

*/
void ids_disconn_call(void);


/*

@Name	ids_mem_type
@Input_Parameter	None
@Output_Parameter	None
@Description	This function selects the memory of OWNER contact stored. 
				On execution of the function the SIM memory is selected in GSM.
@Owner	ASHOK VAISHNAV

*/
void ids_mem_type(void);

/*

@Name	ids_send_sms
@Input_Parameter	Number and Message
@Output_Parameter	None
@Description	This function gets two parameters contact number and the message. 
				On execution of the function it sends the message got as parameter to the number received.
@Owner	ASHOK VAISHNAV

*/
void ids_send_sms(char *, char *);

/*

@Name	ids_sel_sms_mode
@Input_Parameter	None
@Output_Parameter	None
@Description	This function Sets the Mode of GSM for the Sending Messages. 
				On execution of the function it sets the GSM to the TEXT mode.
@Owner	ASHOK VAISHNAV

*/
void ids_sel_sms_mode(void);

#endif /* USART_H_ */