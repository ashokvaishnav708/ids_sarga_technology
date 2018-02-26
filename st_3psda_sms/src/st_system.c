#include <avr/io.h>
#include <st_system.h>
#include <st_alarmsys.h>
#include <st_usart.h>
#include <st_delay.h>
#include <st_msg.h>
/* Activate Whole System */
void ids_system(int stat)
{
	if (stat == ON)
	{
		PORTD |= (1<<PORTD6);

	}
	else if(stat == OFF)
	{
		PORTD &=~ (1<<PORTD6);
		ids_siren(OFF);
		//ids_transmit_discon();
	}
}

void ids_beep()
{
	// Buzzer Notification
	PORTC |= (1<<PINC0);
	ids_delayms(1);
	PORTC &=~ (1<<PINC0);
}
