#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

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