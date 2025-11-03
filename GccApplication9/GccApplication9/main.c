/*
 * GccApplication9.c
 *
 * Created: 2025-04-15 오후 12:12:39
 * Author : jsh
 */ 

#include <avr/io.h>
#define  F_CPU 16000000UL
#include <util/delay.h>

unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
unsigned char help[4] = {0x76, 0x79, 0x38, 0x73};
/*int main()
{
   int i = 0;
   DDRC = 0xff
   DDRG = 0x0f;
   PORTG = 0x01;
   for(i=0; i<10; i++)
   {
	   PORTC = digit[i]; //0~9 를 차례대로 출력.
	   _delay_ms(1000);
   }
}
*/
/*
int main()
{
	int i = 0;
	int set = 0;
	while(1){
		if(set == 0)
		{
	for(i=0;i<500;i++)
	{
		DDRC = 0xff;
		DDRG = 0x0f;
		for(i=0;i<4;i++)
		{
			PORTC = help[3-i];
			PORTG = fnd_sel[i];
			_delay_ms(2);
		}
		_delay_ms(500);
		set = 1;
	}
		}
	
		if (set == 1)
		{
			DDRC = 0x00;
			DDRG = 0x00;
			PORTC = 0x00;
			PORTG = 0x00;
			_delay_ms(500);
			set = 0;
		}
	
	
	}
}
*/

#include <avr/io.h>
#define  F_CPU 16000000UL
#include <util/delay.h>

unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
unsigned char help[4] = {0x76, 0x79, 0x38, 0x73};
int main()
{
	int set = 0;

	while (1)
	{
		if (set == 0)
		{

			for (int j = 0; j < 500; j++) // 약 500 * 2ms = 1초 유지
			{
				DDRC = 0xff; // PORTC 출력 설정
				DDRG = 0x0f; // PORTG 출력 설정

				for (int i = 0; i < 4; i++)
				{
					PORTC = help[3 - i];  // 문자
					PORTG = fnd_sel[i];   // 자리 선택
					_delay_ms(2);         
				}
			}
			set = 1;
		}
		else
		{
			// OFF (전체 꺼짐) 유지 시간
			DDRC = 0x00;
			DDRG = 0x00;
			PORTC = 0x00;
			PORTG = 0x00;
			_delay_ms(500);
			set = 0;
		}
	}
}