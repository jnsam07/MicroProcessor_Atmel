/*
 * motor_2_1.c
 *
 * Created: 2025-05-27 오후 12:09:35
 * Author : jsh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
/*
#define F_CPU 16000000UL
#include <util/delay.h>

volatile unsigned int count = 0;

void run_motor(uint8_t ocr_value) {
	OCR2 = ocr_value; // PWM 듀티 설정
	TCNT2 = 0;        // 타이머 카운터 초기화
	count = 0;

	while (count < 5000);  // 약 5초 대기 (1ms 간격 × 5000회)
}

ISR(TIMER2_COMP_vect)
{
	count++;  // Compare Match 발생 시마다 count++
}

int main()
{
	DDRB |= (1 << PB4);   // 실습용: B4도 출력으로 설정
	DDRD |= (1 << PD7);   // ⚠️ PWM 출력핀 OC2(PD7) 활성화

	TCCR2 = 0x7B;  // Fast PWM, 비반전, 분주 64 (WGM21:WGM20=1, COM21=1, CS22=1|CS21=1)
	TIMSK = 0x80;  // Timer2 Compare Match Interrupt Enable
	sei();         // 전역 인터럽트 활성화

	run_motor(128); // 저속
	run_motor(77);  // 중속
	run_motor(26);  // 고속

	TCCR2 = 0x00;   // 타이머 종료, Normal Mode로 설정 (PWM OFF)
	while (1);      // 무한 대기
}
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int count = 0;

ISR(TIMER2_COMP_vect)
{
	count++;
}

void motor(int sec, int speed_val)
{
	OCR2 = speed_val;   // 속도 설정 (PWM duty)
	TCNT2 = 0;          // 타이머 카운터 초기화
	PORTA = speed_val;  // marking (속도 값 표시용)
	while(count != 1000 * sec); // 지정된 시간까지 대기 (1초당 1000번 인터럽트 발생)
	count = 0;          // count 초기화
}

void motor2(int sec, int speed_val)
{
	OCR2 = speed_val;   // 속도 설정 (PWM duty)
	TCNT2 = 0;          // 타이머 카운터 초기화
	PORTA = 00;  // marking (속도 값 표시용)
	while(count != 1000 * sec); // 지정된 시간까지 대기 (1초당 1000번 인터럽트 발생)
	count = 0;          // count 초기화
}

/*
void STOP(void){
	TCCR2 = 0x01;
	PORTA = 0x00;
	while(count != 1000 * 5);
	count = 0;
}
*/

#define STOP  150
#define LOW  100
#define MID   77
#define HIGH  26


int main(void)
{	while(1){
	DDRA = 0xFF;       // PORTA 전체 출력 (marking용)
	DDRB = 0xFF;       // PORTB 전체 출력 (PB7 = OC2, PB6 = 방향제어)

	TCCR2 = 0x7B;      // Fast PWM, non-inverting, prescaler 64
	TIMSK = 0x80;      // Timer2 Compare Match 인터럽트 활성화
	sei();             // 전역 인터럽트 허용

	motor(5, LOW);     // 저속 5초
	motor(5, MID);     // 중속 5초
	motor(5, HIGH);    // 고속 5초
	motor2(5, STOP); //멈추기
	
	TCCR2 = 0x01;      // Normal mode, prescaler 1 (PWM 중지)
	PORTA = 0x00;      // marking
	
}
}