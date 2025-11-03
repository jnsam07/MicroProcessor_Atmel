/*
 * buzzer_1_3.c
 *
 * Created: 2025-05-13 오후 12:32:42
 * Author : jsh
 */ 

/*
#include <avr/io.h>
#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__ // for Atmel Studio 6
#include <util/delay.h>
void buzzer(int hz, int count);

int main()
{
	DDRB = 0x10;

	while(1)
		{
			buzzer(480, 240);
			buzzer(360, 180);
		}

}


void buzzer(int hz, int count)
{
	int i, ms, us;
	ms = 500/hz;
	us = 500%hz;
	for(i=0; i<count; i++)
	{
		PORTB = 0x10; _delay_ms(ms); _delay_us(us);
		PORTB = 0x00; _delay_ms(ms); _delay_us(us);
	}
}
*/

#include <avr/io.h>
#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__ // for Atmel Studio 6
#include <util/delay.h>
void buzzer(int hz, int count);

int main()
{
	int i;
	DDRB = 0x10;

	while(1)
	{
		for(i=0; i<20; i++)
		{
			buzzer(480, 12);
			buzzer(320, 8);
		}
		_delay_ms(2000);
	}
}

void buzzer(int hz, int count)
{
	int i, ms, us;
	ms = 500/hz;
	us = 500%hz;
	for(i=0; i<count; i++)
	{
		PORTB = 0x10; _delay_ms(ms); _delay_us(us);
		PORTB = 0x00; _delay_ms(ms); _delay_us(us);
	}
}