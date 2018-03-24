#include "Ultrasound_SensorHCSR04.h"
#include "Interrupts_External.h"

Ultrasound_SensorHCSR04 Sensor;


uint32_t distance{0};

void setup(){
  interruptEnable();
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(11, HIGH);
  /*EIMSK = 1;
  EICRA = 2;*/
  interruptSetup(0, 2);
  interruptSetup(1, 2);
}

void loop(){
  distance = Sensor.median();

  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.print("Interrupt 0: ");
  Serial.println(recordedInterrupts[0]);
  Serial.print("Interrupt 1: ");
  Serial.println(recordedInterrupts[1]);

  delay(100);
}
