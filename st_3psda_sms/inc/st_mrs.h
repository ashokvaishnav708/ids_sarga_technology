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

 @File          st_mrs.h 
 
 @Description   This file has header file to operate Magnetic Sensor 

 @author        Nawaj Khan  <nawajk13@yahoo.in>

 @version       $ Initial 1.0  $

 @date          $Date: 2016/12/10 $

 @Cautions      None

 *************************************************************************************
 */


#ifndef  ST_MRS_H_
#define  ST_MRS_H_

/*

@Name	ids_mrs_4
@Input_Parameter	None
@Output_Parameter	Flag
@Description	This checks the 2nd Door Sensor state.
				On execution of the function the system will not check sensors status.
				It returns true or false i.e. 0 or 1.
				It returns 1 if door is opened else 0.
@Owner	NAWAZ KHAN

*/
int ids_mrs_4(void);

/*

@Name	ids_mrs_5
@Input_Parameter	None
@Output_Parameter	Flag
@Description	This checks the 1st Door Sensor state. 
				On execution of the function the system will not check sensors status.
				It returns true or false i.e. 0 or 1.
				It returns 1 if door is opened else 0.
@Owner	NAWAZ KHAN

*/
int ids_mrs_5(void);

/*

@Name	ids_mrs_read
@Input_Parameter	None
@Output_Parameter	flag
@Description	This function checks both Door Sensors(Magnetic Reed Sensors) states. 
				It returns true or false i.e. 0 or 1.
				It returns 0 if door is opened else 1.
@Owner	NAWAZ KHAN

*/
int ids_mrs_read(void);


#endif