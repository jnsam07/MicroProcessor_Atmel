/*
 * GccApplication5.c
 *
 * Created: 2025-04-08 오후 12:21:30
 * Author : jsh
 */ 

#include <avr/io.h>

int main()
{
	DDRA = 0xff;
	while (1)
	{
		PORTA = 0xff;
		delay_sec(1);
		PORTA = 0x00;
		delay_sec(1);
	}
}

