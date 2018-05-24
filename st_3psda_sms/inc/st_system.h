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

 @File          st_system.h 
 
 @Description   This header file contains the prototype functions for system led and beep

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 **************************************************************************************/

#ifndef  ST_System_H_
#define  ST_System_H_

#define ON  1     /* Macro for ON */
#define OFF 0     /* Macro for OFF */


/************Function Prototype*****************/

void ids_set_sys_led(int stat);

void ids_beep(void);

#endif  /* ST_System_H_ */