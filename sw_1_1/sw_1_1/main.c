/*
 * sw_1_1.c
 *
 * Created: 2025-04-22 오후 12:08:15
 * Author : jsh
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{	DDRA = 0xff;
	DDRE = 0x00;
    while (1) 
    {
		if((PINE & 0x10) == 0x00)
			{PORTA = 0xff;
				_delay_ms(10);
			}
		else
			PORTA = 0x00;
    }
}

