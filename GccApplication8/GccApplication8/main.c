/*
 * GccApplication8.c
 *
 * Created: 2025-04-10 오후 12:06:33
 * Author : jsh
 */ 

#include <avr/io.h>


void delay_sec(int sec)
{
	volatile int i,j,k;
	for (i=0;i<sec;i++)
		for (j=0;j<1000;j++)
			for(k=0;k<1000;k++);
}

int main(void)
{
	DDRA = 0xff;
	srand(100);
	while(1)
	{
		PORTA = rand()%256;
		delay_sec(rand()%3);
	}
}

