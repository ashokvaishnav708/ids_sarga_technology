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

 @File          st_mrs.c 
 
 @Description   This file includes the MC operation code to operate Magnetic Sensor
 				
 @author        Nawaj khan <nawajk13@yahoo.com.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *****************************************************************************************/

/*********************Header File Inclusions*********************************************/

 #include <avr/io.h>
 #include <st_mrs.h>
 
/**************************************************************************

@Name	            int ids_mrs_4()
@Input_Parameter	None
@Output_Parameter	Status (integer value)
@Description	    This function is used to read the values of sensor 
                    connected at Port C3.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
 int ids_mrs_4()
 {
	 
	 return (PINC & (1<<PINC3));
 }
 

 /**************************************************************************

@Name	            int ids_mrs_5()
@Input_Parameter	None
@Output_Parameter	Status (integer value)
@Description	    This function is used to read the values of sensor 
                    connected at Port C4.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
 int ids_mrs_5()
 {
	
	 return (PINC & (1<<PINC4));
 }
 
/**************************************************************************

@Name	            int ids_mrs_read()
@Input_Parameter	None
@Output_Parameter	Status (integer value)
@Description	    This function is used to read the values of sensor 
                    connected at Port C3 and C4.
@Owner	            ASHOK VAISHNAV

**************************************************************************/
extern int ids_mrs_read()
{
	int  mrs4, mrs5;
	mrs4 = ids_mrs_4();
	mrs5 = ids_mrs_5();	 
	
	if (mrs4)
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
