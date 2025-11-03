/*
 * motor_1_1.c
 *
 * Created: 2025-05-22 오후 12:00:53
 * Author : jsh
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define MOTOR_CW 0x80
#define MOTOR_CCW 0x40
#define MOTOR_STOP1 0x00
#define MOTOR_STOP2 0xC0

int main(void)
{
	DDRB = 0xff;
	while(1)
	{
		PORTB = MOTOR_CW;
		_delay_ms(5000);
		PORTB = MOTOR_STOP1;
		_delay_ms(3000);
		PORTB = MOTOR_CCW;
		_delay_ms(5000);
		PORTB = MOTOR_STOP2;
		_delay_ms(3000);
	}
}