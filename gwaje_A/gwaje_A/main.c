/*
 * gwaje_A.c
 *
 * Created: 2025-04-10 오후 12:18:49
 * Author : jsh
 */ 

#include <avr/io.h>
#include F_CPU 16000000UL
#include <util/delay.h>
// 0.1초 지연 함수
/*void delay_sec(int sec)
{
	volatile int i,j,k;
	for(i=0;i<sec*10;i++) // 0.1초 단위로 만들기 위해 sec*10
	for(j=0;j<1000;j++)
	for(k=0;k<1000;k++);
}
*/

int main(void)
{
	int i;
	DDRA = 0xFF;  // 포트 A 전체 출력 설정

	while (1)
	{
		// 점점 밝아짐: 1개 ON ~ 8개 ON
		for (i = 1; i <= 8; i++)
		{
			PORTA = (1 << i) - 1;
			_delay_ms(100);
		}

		// 점점 어두워짐: 7개 ON ~ 1개 ON
		for (i = 7; i >= 1; i--)
		{
			PORTA = (1 << i) - 1;
			_delay_ms(100);
		}
	}
}
/* int main(void)
{
	unsigned char data = 0x01;  // 초기값: 가장 오른쪽 비트가 켜짐 (0000 0001)
	unsigned char direction = 0; // 0 = 왼쪽으로 이동, 1 = 오른쪽으로 이동

	DDRA = 0xFF; // PORTA를 출력으로 설정

	while (1)
	{
		for(i=0;i<=6;i++)
		{
			PORTA = 0x01;
			_delay_ms(100)
			PORTA = 0x03;
			PORTA = 0x07;
			PORTA = 0x0f;
			PORTA = 0x1f;
			PORTA = 0x3f;
			PORTA = 0x7f;
			PORTA = 0xff
		}
		}
	}
}

