#ifndef PID_H
#define PID_H

#include <Arduino.h>

#define DEFAULT_KP 10
#define DEFAULT_KI 10
#define DEFAULT_KD 10
#define DEFAULT_INTERVALTIME 100

uint32_t nmillis;

class PIDClass{
private:
	double kP, kI, kD;
	uint16_t intervalTime;
	uint32_t now, previous;
	int32_t errorP, errorI, errorD;
	uint32_t output;
	int32_t timeSinceLast;
	double errorPLast;

	void setDefaults(){
		kP = DEFAULT_KP;
		kI = DEFAULT_KI;
		kD = DEFAULT_KD;
		intervalTime = DEFAULT_INTERVALTIME;
		now = millis();
	}

public:
	PIDClass(){setDefaults();}
	PIDClass(double input_kP, double input_kI, double input_kD, uint16_t input_intervalTime){
		kP = input_kP;
		kI = input_kI;
		kD = input_kD;
		intervalTime = input_intervalTime;
		now = millis();
	}
	
	uint8_t compute(double currentSpeed, double desiredSpeed){
		
		previous = now;
		now = nmillis;
		
		timeSinceLast = now - previous;
		
		errorPLast = errorP;
		
		errorP = desiredSpeed - currentSpeed;
		errorI += (errorP * timeSinceLast);
		errorD = (errorP - errorPLast) / timeSinceLast;		
		
		output = kP*errorP + kI*errorI;// + kD*errorD;

		if(output > 255){
			output = 255;
		}
		
		if(errorI > 50000 || errorI < -50000){
			resetPID();
		}
		
		
		return (uint8_t)output;
	}
	
	void resetPID(){
		errorP = 0;
		errorI = 0;
		errorD = 0;
	}
	
	uint32_t get_errorP(){
		return errorP;
	}
	
	uint32_t get_errorI(){
		return errorI;
	}
};

#endif
