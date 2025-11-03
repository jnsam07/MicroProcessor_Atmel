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