#include <avr/io.h>
#include F_CPU 
#include <util/delay.h>
int main(void)
{
	DDRA = 0xff;
	DDRE = 0x00;
	while (1)
	{
		if ((PINE & 0x10) == 0x00){
			PORTA = 0x80;
			_delay_ms(10);
		}
		else if ((PINE & 0x20) == 0x00){
			PORTA = 0x01;
			_delay_ms(10);
		}
		else
		{
			PORTA = 0x00;
			_delay_ms(10);
		}
	}
}