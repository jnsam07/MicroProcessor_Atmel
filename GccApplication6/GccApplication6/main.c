#include <avr/io.h>


void delay_sec(int sec)
{
	volatile int i,j,k;
	for(i=0;i<sec;i++)
		for(j=0;j<1000;j++)
			for(k=0;k<1000;k++);
}

int main()
{
	unsigned char count=0;
	DDRA = 0xff;
	while(1)
	{
		count = count + 1;
		PORTA = count;
		delay_sec(1);
	}
}




/*int main()
{
	unsigned char data=0x01;
	DDRA = 0xff;
	while(1)
	{
		PORTA = data;
		data = (data*2);
		delay_sec(1);
		if(PORTA==128)
		data = 1;
	}
}

/*int main()
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
*/

/*int main()
{
	unsigned char count=0;
	DDRA = 0xff;
	while(1)
	{
		count = count + 1;
		PORTA = count;
		delay_sec(1);
	}
}
*/

