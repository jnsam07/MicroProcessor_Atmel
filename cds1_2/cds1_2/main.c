#include <avr/io.h>
#define CDS_100LUX 1200
#define CDS_10LUX  871
#define CDS_1LUX  600

void init_adc();
unsigned short read_adc();
void show_adc(unsigned short data);

void init_adc()
{
	ADMUX = 0x00; 
	ADCSRA = 0x87; 
}

unsigned short read_adc()
{
	unsigned char adc_low, adc_high;
	unsigned short value;

	ADCSRA |= (1 << ADSC); // 변환 시작
	while ((ADCSRA & (1 << ADIF)) == 0); // 변환 완료 대기

	adc_low = ADCL;  // 반드시 먼저 읽기
	adc_high = ADCH;

	value = (adc_high << 8) | adc_low;

	return value;
}

void show_adc(unsigned short data)
{
	if (data > CDS_100LUX)
	{
		PORTA = 0x00; // 모두 OFF
	}
	else if (data > CDS_10LUX)
	{
		PORTA = 0x81; 
	}
	else if (data > CDS_1LUX)
	{
		PORTA = 0x55; 
	}
	else
	{
		PORTA = 0xFF; 
	}
}

int main()
{
	unsigned short value;
	DDRA = 0xff; // LED 출력 설정
	init_adc(); // ADC 초기화
	while(1)
	{
		value = read_adc();  // ADC 변환값 읽기
		show_adc(value);     // LED 출력 제어
	}
}