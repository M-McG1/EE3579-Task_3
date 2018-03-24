#ifndef INTERRUPTS_INTERNAL_H_INCLUDED
#define INTERRUPTS_INTERNAL_H_INCLUDED

#include <Arduino.h>
#include <Interrupts_External.h>

uint8_t com0a = 0;
uint8_t com0b = 0;
uint8_t wgm = 8;
uint8_t cs0 = 3;
uint8_t counter = 0;
uint32_t activations[8];
uint16_t time;

void timer_setup(uint16_t a){
	
	time = a;
	time /= 10;
	
	TCCR0A |= (com0a << 6); //COM0A
	TCCR0A |= (com0b << 4); //COM0B
	TCCR0A |= (wgm & !252); //WGM 01,00
	
	TCCR0B |= ((wgm & !251) << 3);  //WGM 02
	TCCR0B |= (cs0 << 0); //CS0
		
	OCR0A = 141;	
	OCR0B = 107;
	
	TIMSK0 = 2;
	
	
	//DDRD = (1 << PD5);
}

ISR(TIMER0_COMPA_vect){
	if(counter == time){
		counter = 0;
		activations[0] = recordedInterrupts[0];
		activations[1] = recordedInterrupts[1];
		activations[0] = 0;
		activations[1] = 0;
	}
	else{counter++;}
}

#endif