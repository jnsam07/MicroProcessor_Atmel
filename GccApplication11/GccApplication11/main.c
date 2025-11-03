#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ON 1
#define OFF 0

// 음계에 대응하는 Timer0 초기값 (8비트, 16MHz, 32분주 기준)
#define DO_data   17
#define RE_data   43
#define MI_data   66
#define FA_data   77
#define SOL_data  97
#define LA_data   114
#define TI_data   117
#define HDO_data  137
#define SILENT    0

volatile int state = OFF;
volatile int tone = DO_data;

// Timer0 Overflow Interrupt
ISR(TIMER0_OVF_vect)
{
	if (tone == SILENT) {
		PORTB = 0x00;
		return;
	}

	if (state == ON) {
		PORTB = 0x00;
		state = OFF;
		} else {
		PORTB = 0x10; // B4 ON
		state = ON;
	}
	TCNT0 = tone;
}

// 음 재생 함수 (딜레이 반복으로 구현)
void play_note(int note, int duration_ms)
{
	tone = note;
	for (int i = 0; i < duration_ms; i++) {
		_delay_ms(1);
	}
	tone = SILENT;
	for (int i = 0; i < 50; i++) {
		_delay_ms(1);
	}
}

int main()
{
	DDRB = 0x10;       // B4 출력
	TCCR0 = 0x03;      // Timer0: 32분주
	TIMSK = 0x01;      // Timer0 Overflow Interrupt Enable
	TCNT0 = DO_data;   // 초기값
	sei();             // 전역 인터럽트 허용

	// 산토끼 멜로디
	int melody[] = {
		SOL_data, SOL_data, LA_data, LA_data, SOL_data, SOL_data, MI_data,   // 학교종이 땡떙땡
		SOL_data, SOL_data, MI_data, MI_data, RE_data,  // 어서 모이자
		SOL_data, SOL_data, LA_data, LA_data, SOL_data, SOL_data, MI_data, // 선생님의 우리를
		SOL_data, MI_data, RE_data, MI_data, DO_data            // 기다리신다
	};

	// 음 길이 (ms 단위)
	int duration[] = {
		8000, 8000, 8000, 8000, 8000, 8000, 16000,
		8000, 8000, 8000, 8000, 24000,
		8000, 8000, 8000, 8000, 8000, 8000, 16000,
		8000, 8000, 8000, 8000, 24000
	};

	int notes = sizeof(melody) / sizeof(int);

	while (1)
	{
		for (int i = 0; i < notes; i++)
		{
			play_note(melody[i], duration[i]);
		}
		for (int i = 0; i < 1000; i++) {
			_delay_ms(1);
		}
	}
}