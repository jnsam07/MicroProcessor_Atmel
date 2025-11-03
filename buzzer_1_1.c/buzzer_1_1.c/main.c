/*
 * buzzer_1_1.c.c
 *
 * Created: 2025-05-13 오후 12:06:48
 * Author : jsh
 */ 

#include <avr/io.h>

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
int main()
{
	DDRB = 0x10;
	while(1)
	{
		PORTB = 0x10; _delay_ms(2);
		PORTB = 0x00; _delay_ms(2);
	}
}