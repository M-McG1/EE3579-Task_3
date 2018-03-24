#ifndef INTERRUPTS_EXTERNAL_H_INCLUDED
#define INTERRUPTS_EXTERNAL_H_INCLUDED

#include <Arduino.h>

uint32_t recordedInterrupts[8];

void interruptEnable(){
	sei();
}

void interruptSetup(uint8_t interrupt, uint8_t setting){
		EIMSK |= (1 << interrupt);

		if(interrupt <= 3){
			interrupt *= 2;
			EICRA |= (setting << interrupt);
		}

		/*if(interrupt >= 4 && interrupt <= 7){
			interupt -= 4;
			interupt *= 2;
			EICRB |= (setting << interrupt);
		}*/

		else{}
}

ISR(INT0_vect){
	recordedInterrupts[0]++;
}

ISR(INT1_vect){
	recordedInterrupts[1]++;
}

/*ISR(INT2_vect){
	recordedInterrupts[2]++;
}

ISR(INT3_vect){
	recordedInterrupts[3]++;
}

ISR(INT4_vect){
	recordedInterrupts[4]++;
}

ISR(INT5_vect){
	recordedInterrupts[5]++;
}

ISR(INT6_vect){
	recordedInterrupts[6]++;
}

ISR(INT7_vect){
	recordedInterrupts[7]++;
}*/

#endif