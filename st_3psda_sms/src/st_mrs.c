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

 @File          st_mrs.c 
 
 @Description   This file includes the MC operation code to operate Magnetic Sensor
 				
 @author        Nawaj khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 ****************************************************************************************
 */

/*								Header File Inclusions
*****************************************************************************************/

 #include <avr/io.h>
 #include <st_mrs.h>

 /* Pull down Pin B1 */
/* int ids_mrs_1()
 {
	 return (PINC & (1<<PINC0));
 }
 */
 /* Pull down Pin B2 */
 /*int ids_mrs_2()
 {
	 return (PINC & (1<<PINC1));
 }*/
 
 /* Pull down Pin B3 */
 int ids_mrs_3()
 {
	 return (PINC & (1<<PINC2));
 }
 
 /* Pull down Pin B4 */
 int ids_mrs_4()
 {
	 
	 return (PINC & (1<<PINC3));
 }
 
 /* Pull down Pin B5 */
 int ids_mrs_5()
 {
	
	 return (PINC & (1<<PINC4));
 }
 
 extern int ids_mrs_read()
 {
	int  mrs1, mrs2, mrs3, mrs4, mrs5;

//	mrs1 = ids_mrs_1();
	//mrs2 = ids_mrs_2();
	mrs3 = ids_mrs_3();
	mrs4 = ids_mrs_4();
	mrs5 = ids_mrs_5();	 
	
/*	if (mrs1==0||mrs2==0||mrs3==0)
	{
		return 0 ;
	}
	else*/ if (mrs4)
	{
		return 0 ;
	}
	else if (mrs5)
	{
		return 0 ;
	}
	else
	{
		return 1 ;
	}
	 
 }
