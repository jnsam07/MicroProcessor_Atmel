


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define F_CPU 16000000UL

#define LOW    128
#define MID     77
#define HIGH    26
#define STOP     0

volatile uint8_t set_time = 0;
volatile uint8_t run_flag = 0;
volatile uint32_t count_ms = 0;
volatile uint16_t breeze_count = 0;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;

uint8_t digit[10] = {
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7C, 0x07,
	0x7F, 0x67
};

uint8_t fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
volatile uint8_t fnd_buf[4] = {0, 0, 0, 0};

// === SW1: 시간 설정 ===
ISR(INT4_vect) {
	if (!run_flag && set_time < 99)
	set_time++;
}

// === SW2: 동작 시작 ===
ISR(INT5_vect) {
	if (set_time > 0) {
		run_flag = 1;
		minutes = set_time;
		seconds = 0;
		count_ms = 0;
		breeze_count = 0;

		// PWM 시작
		TCCR2 = 0x7B;  // Fast PWM, non-inverting, 64분주
	}
}

// === 1ms 주기 타이머: 시간 감소 + 자연풍 ===
ISR(TIMER0_COMP_vect) {
	count_ms++;
	breeze_count++;

	if (breeze_count >= 1000) {
		breeze_count = 0;
		if (run_flag) {
			uint8_t speeds[] = {LOW, MID, HIGH};
			OCR2 = speeds[rand() % 3];
		}
	}

	if (count_ms >= 1000) {
		count_ms = 0;
		if (seconds == 0) {
			if (minutes > 0) {
				minutes--;
				seconds = 59;
				} else {
				run_flag = 0;
				OCR2 = STOP;
				TCCR2 = 0x00;  // PWM 정지
			}
			} else {
			seconds--;
		}
	}
}

// === FND 버퍼 업데이트 ===
void update_fnd_buf(uint8_t min, uint8_t sec) {
	fnd_buf[3] = min / 10;
	fnd_buf[2] = min % 10;
	fnd_buf[1] = sec / 10;
	fnd_buf[0] = sec % 10;
}

// === FND 다이내믹 디스플레이 ===
void display_fnd_loop() {
	for (int i = 0; i < 4; i++) {
		PORTC = digit[fnd_buf[i]];
		if (i == 2) PORTC |= 0x80;  // 소수점 (MM.SS 표시)
		PORTG = fnd_sel[i];
		_delay_ms(1);
	}
}

// === 초기화 함수들 ===
void init_interrupts() {
	EIMSK |= (1 << INT4) | (1 << INT5);
	EICRB |= (1 << ISC41) | (1 << ISC40); // INT4 상승엣지
	EICRB |= (1 << ISC51) | (1 << ISC50); // INT5 상승엣지
}

/*void init_timer0_ctc() {
	TCCR0 = 0x0B;   // CTC 모드, 64분주
	OCR0 = 250;     // 1ms 타이머
	TIMSK |= (1 << OCIE0);
}
*/

void init_timer0_ctc() {
	TCCR0 = (1 << WGM01);                // CTC 모드 설정 (WGM01 = 1)
	TCCR0 |= (1 << CS01) | (1 << CS00);  // 분주비 64 설정 (CS01=1, CS00=1)
	OCR0 = 249;                          // 1ms 인터럽트용
	TIMSK |= (1 << OCIE0);               // 출력비교 인터럽트 허용
}

void init_pwm_motor() {
	DDRB |= (1 << PB7);  // OC2 (PWM 출력 핀)
	DDRB |= (1 << PB6);  // 방향 고정
	PORTB &= ~(1 << PB6);

	TCCR2 = 0x00;  // 초기에는 PWM 꺼짐
	OCR2 = STOP;
}

void init_fnd() {
	DDRC = 0xFF;  // 세그먼트 출력
	DDRG = 0x0F;  // 자릿수 선택
}

// === 메인 ===
int main(void)
{
	init_interrupts();
	init_timer0_ctc();
	init_pwm_motor();
	init_fnd();
	sei();

	while (1)
	{
		if (!run_flag)
		update_fnd_buf(set_time, 0);
		else
		update_fnd_buf(minutes, seconds);

		display_fnd_loop();
	}
}