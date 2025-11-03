#include <avr/io.h>
#define NULL 0

void putchar0(char c)
{
	while (!(UCSR0A & 0x20));  // 송신 가능 대기
	UDR0 = c;
}

char getchar0(void)
{
	while (!(UCSR0A & 0x80));  // 수신 대기
	return UDR0;
}

void print_prompt(void)
{
	char prompt[] = "JKIT-128-1> ";
	int i = 0;
	while (prompt[i] != NULL)
	putchar0(prompt[i++]);
}

int main(void)
{
	char ch;

	// UART 설정
	UBRR0H = 0;
	UBRR0L = 8; // 16MHz, 115000 baud 설정 (Datasheet 기준, UBRR = 8)
	UCSR0B = 0x18; // RX Enable + TX Enable
	UCSR0C = 0x06; // 8 Data bit, no parity, 1 Stop bits

	print_prompt(); // 첫 프롬프트 출력

	while (1)
	{
		ch = getchar0(); // 문자 수신
		putchar0(ch);    // 에코

		// Enter 키(= '\r' 또는 '\n' depending on terminal) 처리
		if (ch == '\r' || ch == '\n')
		{
			putchar0('\n');
			putchar0('\r');
			print_prompt();
		}
	}
}