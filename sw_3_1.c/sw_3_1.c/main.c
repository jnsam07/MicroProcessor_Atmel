/*
 * sw_3_1.c.c
 *
 * Created: 2025-05-01 오후 12:18:09
 * Author : jsh
 */ 

/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define STOP 0;
#define  GO 1;
volatile int cur_time=0;
volatile int stop_time=0;
volatile int state = STOP;
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07,
0x7f, 0x67};
unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};


int main(void)
{
	DDRA = 0xff;
	DDRE = 0x00;
	state = STOP;
	EICRB = 0x0a; // INT4, INT5 = falling edge
	EIMSK = 0x30; // INT4, INT5 interrupt enable
	SREG |= 1<<7; // SREG bit7 = I (Interrupt Enable)
	while (1)
	{
		cur_time++
		if(state == STOP)
		{
			display_fnd(stop_time)
		}
		else
		{
			display_fnd(cur_time)
		}
	}
	display_fnd(count); // FND Display
	
	
	
}


ISR(INT4_vect)
{
	if(state == STOP)
	{
		state = GO;
	}
	else
	{
		state = STOP;
		cur_time = stop_time;
		
	}
}

void display_fnd(int a)
{ int i, fnd[4];
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
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define STOP 0
#define GO 1

volatile int cur_time = 0;     // 1/100초 단위 시간
volatile int stop_time = 0;
volatile int state = STOP;

unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f,
	0x66, 0x6d, 0x7d, 0x07,
0x7f, 0x6f}; // 0~9 FND
unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};

void display_fnd(int time);

int main(void)
{
	DDRA = 0xFF;    // 포트 A는 출력 (FND 값)
	DDRC = 0xFF;    // FND 데이터
	DDRG = 0x0F;    // FND 선택 신호
	DDRE &= ~((1 << PE4) | (1 << PE5)); // SW1, SW2 입력

	// 외부 인터럽트 설정 (SW1 = INT4, SW2 = INT5)
	EICRB = 0x0A; // INT4, INT5: Falling edge
	EIMSK = (1 << INT4) | (1 << INT5);
	SREG |= (1 << 7); // 전역 인터럽트 활성화

	// 타이머 설정 (Timer0, CTC 모드, 10ms 주기)
	TCCR0 = (1 << WGM01) | (1 << CS02); // CTC, 64분주
	OCR0 = 249; // 16MHz / 64 분주 → 250 주기로 1ms, 250x10 = 10ms
	TIMSK |= (1 << OCIE0); // 비교 일치 인터럽트 허용

	while (1)
	{
		if (state == GO)
		display_fnd(cur_time);
		else
		display_fnd(stop_time);
	}
}

// 타이머0 비교일치 인터럽트 (10ms마다 발생)
ISR(TIMER0_COMP_vect)
{
	static int count_10ms = 0;

	if (state == GO)
	{
		count_10ms++;
		if (count_10ms >= 10) // 100ms x 10 = 1초
		{
			count_10ms = 0;
			cur_time++; // 1/100초 단위 증가
		}
	}
}

// SW1: GO <-> STOP 전환
ISR(INT4_vect)
{
	if (state == STOP)
	state = GO;
	else
	{
		state = STOP;
		stop_time = cur_time;
	}
}

// SW2: 리셋
ISR(INT5_vect)
{
	cur_time = 0;
	stop_time = 0;
	state = STOP;
}

// FND 출력 (형식: SS.hh)
void display_fnd(int time)
{
	int ss = time / 100;      // 초 단위
	int hh = time % 100;      // 1/100초 단위

	int num[4] = {
		ss / 10,      // 10초
		ss % 10,      // 1초
		hh / 10,      // 1/10초
		hh % 10       // 1/100초
	};

	for (int i = 0; i < 4; i++)
	{
		PORTG = fnd_sel[i];

		if (i == 2)
		PORTC = digit[num[i]] | 0x80; // 소수점 찍기
		else
		PORTC = digit[num[i]];

		_delay_ms(2);
	}
}