#ifndef ULTRASOUND_SENSORHCSR04_H_INCLUDED
#define ULTRASOUND_SENSORHCSR04_H_INCLUDED

#include <Arduino.h>

#define SPEED_OF_SOUND 340	//Speed of sound in current atmosphere.
#define MAX_RANGE 3000		//(In mm) Accuracy Tails off > 3500 mm.

#define DEFAULT_MEDIAN 3	//Default no. of readings before returning value.
#define MAX_MEDIAN 7		//Max no. of readings before returning value.

#define DEFAULT_TRIGGER_PIN 12	//Trigger pin default.
#define DEFAULT_ECHO_PIN 13		//Echo pin default.

class Ultrasound_SensorHCSR04{
private:
	
	uint8_t trigger_pin, echo_pin, counterA, counterB;
	uint32_t duration;
	uint32_t store[MAX_MEDIAN];
public:

	/*Standard constructor, sets default pins.
	 */
	Ultrasound_SensorHCSR04();
	
	/*Custom constructor, sets custom pins.
	 */
	Ultrasound_SensorHCSR04(uint8_t trigger_p, uint8_t echo_p);

	/*Requests single distance reading from sensor, fastest response.
	 */
	uint32_t ping();

	/*Requests the DEFAULT_MEDIAN readings from sensor and returns the median.
	 */
	uint32_t median();

	/*Requests a custom number of readings from sensor (up to the MAX_MEDIAN)
	 *and returns the median.
	 */
	uint32_t median(uint8_t trigger_p);
};

#endif