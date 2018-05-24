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


/***************************************************************************************

 @File			ST_Port.c 
 
 @Description   This file includes the MC operation code of Port Initialization 
				& Set Direction Register
 				
 @author        Nawaj khan <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *****************************************************************************************/

/*************Header File Inclusions *****************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <st_usart.h>
#include <util/delay.h>
#include <st_port.h>

/**************************************************************************

@Name	            ids_port_init()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to initialize the ports
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_port_init()
{
	/* Initialization Sensor's Pins  */
	/* Sensor's Pin declared as Output */
	DDRB |= (1<<PINB1);
	/* Buzzer Pin declared as Input */
	DDRC |= (1<<PINC0);
	DDRD |= ((1<<PIND7)|(1<<PIND6)|(1<<PIND5)|(1<<PIND4)); 
	PORTC |= ((1<<PINC1)|(1<<PINC2)|(1<<PINC3)|(1<<PINC4)|(1<<PINC5));
	PORTD |= (/*(1 << PIND2)|(1 <<PIND3)|*/(1<<PIND7)|(1<<PIND4));    // turn On the Pull-up
}
/**************************************************************************

@Name	            ids_extint_init()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to initialize and enbale the
                    external interrupts.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
void ids_extint_init()
{
	// PD0 is now an input with pull-up enabled
	GICR |= ((1 << INT0)|(1 << INT1));      // Turns on INT0
	MCUCR = 0x05;
	sei();                    // turn on interrupts
}

/**************************************************************************

@Name	            ids_panic_btn_status()
@Input_Parameter	None
@Output_Parameter	None
@Description	    This function is used to read the panic button.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
int ids_panic_btn_status()
{
	
	return ((PINC & (1<<PINC1))==0);
}