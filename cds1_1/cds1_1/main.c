#include <avr/io.h>
#define CDS_VALUE 871
void init_adc();
unsigned short read_adc();
void show_adc(unsigned short data);


int main()
{
	unsigned short value;
	DDRA = 0xff;
	init_adc(); // ADC 초기화(함수 처리)
	while(1)
	{
		value = read_adc();  // AD 변환 시작 및 결과 읽어오기 (함수로 처리)
		show_adc(value); // 값을 비교하여 LED ON 또는 OFF (함수로 처리)
	}
}

void init_adc()
{
	ADMUX = 0x00;
	// REFS(1:0) =“00” AREF(+5V) 기준전압 사용
	// ADLAR =‘0’ 디폴트 오른쪽 정렬
	// MUX(4:0) =“00000” ADC0 사용, 단극 입력
	ADCSRA = 0x87;
	// ADEN =‘1’ ADC를 Enable
	// ADFR =‘0’ single conversion(한번만 변환) 모드
	// ADPS(2:0) =“111” 프리스케일러 128분주, 0.125Mhz 주기
}

unsigned short read_adc()
{
	unsigned char adc_low, adc_high;
	unsigned short value;
	ADCSRA |= (1<<ADSC); // ADC start conversion ADSC =‘1'
	while ((ADCSRA & (1<<ADIF)) == 0); // ADC 변환 완료(ADIF) 검사
	adc_low = ADCL; // 변환된 Low 값 읽어오기 (반드시 먼저!)
	adc_high = ADCH; // 변환된 High 값 읽어오기
	value = (adc_high << 8) | adc_low;  // value 는 High 및 Low 연결 16비트값
	return value;
}

void show_adc(unsigned short data)
{
	if (data <= CDS_VALUE) // 기준값보다 작거나 같으면
	PORTA = 0xff; // 가로등(LED) ON
	else // 기준값 이상이면
	PORTA = 0x00; // 가로등(LED) OFF
}