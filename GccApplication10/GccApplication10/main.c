/*
 * GccApplication10.c
 *
 * Created: 2025-04-17 오후 12:01:20
 * Author : jsh
 */ 

	#include <avr/io.h>
	#define F_CPU 16000000UL
	#include <util/delay.h>

int main(void)
{
	int i = 0, count = 0;
	DDRC = 0xff;
	DDRG = 0x0f;
	while(1)
	{
		count++
		if(count == 100000)
		count = 0;
		fnd[3] = (count/1000)%10;
		fnd[2] = (count/100)%10;
		fnd[1] = (count/10)%10;
		fnd[0] = count%10;
		for (i=0;i<4;i++)
		{
			PORTC = digit[fnd[i]]
			PORTG = fnd_sel[i]
			_delay_ms(2);
			if(i%2) _delay_ms(1);
		}
	}
}



