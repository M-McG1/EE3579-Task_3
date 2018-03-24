#include "Ultrasound_Sensor-HC-SR04.h"

Ultrasound_SensorHCSR04::Ultrasound_SensorHCSR04():
trigger_pin{DEFAULT_TRIGGER_PIN}, echo_pin{DEFAULT_ECHO_PIN}{
		
	pinMode(trigger_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
}

Ultrasound_SensorHCSR04::Ultrasound_SensorHCSR04(uint8_t trigger_p, uint8_t echo_p):
	trigger_pin{trigger_p}, echo_pin{echo_p}{
		
	pinMode(trigger_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
}

uint32_t Ultrasound_SensorHCSR04::ping(){
	
	digitalWrite(trigger_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigger_pin, HIGH);
	delayMicroseconds(20);
	digitalWrite(trigger_pin, LOW);
	
	duration = pulseIn(echo_pin, HIGH, MAX_RANGE / SPEED_OF_SOUND * 2000);
	
	return duration * SPEED_OF_SOUND / 2000;
}

uint32_t Ultrasound_SensorHCSR04::median(){
		
	return median(DEFAULT_MEDIAN);
}

uint32_t Ultrasound_SensorHCSR04::median(uint8_t trigger_p){
	
	if(trigger_p > MAX_MEDIAN){trigger_p = MAX_MEDIAN;}
	if(trigger_p < 3){return ping();}
	
	for(counterA = 0; counterA < trigger_p; counterA++){
		store[counterA] = ping();
	}

	for(counterA = 0; counterA < trigger_p; counterA++){
		for(counterB = 0; counterB < trigger_p; counterB++){
			if(store[counterB] > store[counterB + 1]){
				duration = store[counterB + 1];
				store[counterB + 1] = store[counterB];
				store[counterB] = duration;
			}
		}
	}
	
	/*for(counterA = 0; counterA < trigger_p; counterA ++){
		Serial.print(counterA);
		Serial.print(": ");
		Serial.println(store[counterA]);
	}*/
	
	return store[(trigger_p + trigger_p % 2)/2-1];
}