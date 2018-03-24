#include "Ultrasound_SensorHCSR04.h"

Ultrasound_SensorHCSR04 Sensor;

uint32_t distance{0};

void setup(){
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
}

void loop(){
  distance = Sensor.median();

  Serial.println(distance);
  Serial.println("");

  //delay();
}
