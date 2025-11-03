/*
 * sw2_2.c
 *
 * Created: 2025-04-29 오후 12:47:49
 * Author : jsh
 */ 

#include <avr/io.h> // ATmega128 register 정의
#include <avr/interrupt.h> // interrupt 관련
#define F_CPU 16000000UL
#include <util/delay.h>
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07,
0x7f, 0x67};
unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
volatile int count = 0;

 int main(void)
 {
	 DDRA = 0xff;
	 DDRE = 0x00;
	 SREG |= 0x80;
	 EIMSK = 0x30;
	 EICRB = 0x00;
	 while (1)
	 PORTA = 0x00;
 }

ISR(INT4_vect)
{
	count++;
	_delay_ms(10); EIFR |= 1 << 4;
}

ISR(INT5_vect)
{
	count = 0;
}

void display_fnd(int count)
{
	int i, fnd[4];
	fnd[3] = (count/1000)%10;
	fnd[2] = (count/100)%10;
	fnd[1] = (count/10)%10;
	fnd[0] = count%10;
	for (i=0; i<4; i++)
	{
		PORTC = digit[fnd[i]];
		PORTG = fnd_sel[i];
		_delay_ms(2);
	}
}