/*
 * sw2_1_re.c
 *
 * Created: 2025-04-29 오후 12:44:33
 * Author : jsh
 */ 

#include <avr/io.h>


 #include <avr/io.h>
 #include <avr/interrupt.h>
 int main(void)
 {
	 DDRA = 0xff;
	 DDRE = 0x00;
	 SREG |= 0x80;
	 EIMSK = 0x30;
	 EICRB = 0x00;
	 while (1)
	 PORTA = 0x00;
 }
 ISR (INT4_vect)
 {
	 PORTA = 0x80;
 }
 ISR (INT5_vect)
 {
	 PORTA = 0x01;
 }
