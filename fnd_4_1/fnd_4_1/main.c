/*
 * fnd_4_1.c
 *
 * Created: 2025-04-17 오후 12:37:21
 * Author : jsh
 */ 

	#include <avr/io.h>
	#define F_CPU 16000000UL
	#include <util/delay.h>
	
	unsigned char digit[10] = {0x3f, 0x06,0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07,0x7f, 0x67};
	unsigned char fnd_sel[4] = {0x01,0x02, 0x04, 0x08};
	unsigned char tel[16] = {
		0x3F, // 0
		0x06, // 1
		0x3F, // 0
		0x40, // -
		0x66, // 4
		0x3F, // 0
		0x7D, // 6
		0x7F, // 8
		0x40, // -
		0x6D, // 5
		0x7D, // 6
		0x6F, // 9
		0x7D, // 6
		0x00, // x
		0x00, // x
		0x00 // x
	};



int main(void)
{
	int i, j, k;
	DDRC = 0xFF; // PORTC = FND 데이터
	DDRG = 0x0F; // PORTG = FND 자리 선택

	while (1)
	{
		// 0~(13-4) = 0~9까지 4자리 슬라이딩
		for (i = 0; i <= 12; i++)
		{
			for (k = 0; k < 100; k++) // 4자리 조합을 100번 반복하여 눈에 보이게 함 (0.5초 정도)
			{
				for (j = 0; j < 4; j++)
				{
					PORTC = tel[i + (3 - j)]; // 오른쪽부터 표시
					PORTG = fnd_sel[j];           // 자리 선택
					_delay_ms(2);
				}
			}
			_delay_ms(500); // 다음 화면으로 넘어가기 전 0.5초 정지
		}
	}
}

