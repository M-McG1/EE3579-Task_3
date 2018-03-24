#include "Ultrasound_SensorHCSR04.h"
#include "Interrupts_External.h"
#include "Interrupts_Internal.h"

Ultrasound_SensorHCSR04 Sensor;


uint32_t distance{0};

void setup(){
  sei();
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(11, HIGH);
  
  interruptSetup(0, 2);
  interruptSetup(1, 2);
  timer_setup(100);
}

void loop(){
  distance = Sensor.median();

  Serial.print(",Distance: ");
  Serial.println(distance);

  Serial.print(",Activations 0: ");
  Serial.println(activations[0]);
  Serial.print(",Activations 1: ");
  Serial.println(activations[1]);

  delay(100);
}
