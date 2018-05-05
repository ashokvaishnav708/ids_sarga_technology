#ifndef  ST_System_H_
#define  ST_System_H_
#define ON 1
#define OFF 0


/*

@Name	ids_set_sys_led
@Input_Parameter	state
@Output_Parameter	None
@Description	This function is to toggle the System LED.
				This LED is used for ARM and DISARM notification.
@Owner	NAWAZ KHAN

*/
void ids_set_sys_led(int stat);


/*

@Name	ids_beep
@Input_Parameter	state
@Output_Parameter	None
@Description	This function simply beeps the buzzer for 500 milliseconds.
				This beep is used as notification of System ARM and DISARM.
@Owner	ASHOK VAISHNAV

*/
void ids_beep(void);

#endif  /* ST_System_H_ */