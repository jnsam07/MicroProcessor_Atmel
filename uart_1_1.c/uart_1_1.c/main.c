#include <avr/io.h>
#define NULL 0
void putchar0(char c)
{
	while(!(UCSR0A & 0x20));
	UDR0 = c;
}

void getchar0(char i)
{
	while(!(UCSR0A ))
}

int main()
{
	int i;
	char data[] = "Happy New Year!\n\r";


UBRR0H = 0;
UBRR0L = 8; // 12비트가 의미를 가짐,
						// ATmega128 datasheet 참조 요망
						// 16Mhz, 115200 baud의 경우
UCSR0B = 0x18; // Transmit(TX) Enable
UCSR0C = 0x06; // UART Mode, 8 Bit Data, even Parity, 2 Stop Bit

while(1) // 연속적으로 보내기
	{
		i=0;
		while (data[i]!= NULL) // check String End
		putchar0(data[i++]); // 순서대로 보내기
	}
}