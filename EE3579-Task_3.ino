#include "Arduino.h"
#include "Ultrasound_SensorHCSR04.h"
#include "Interrupts_External.h"
#include "Interrupts_Internal.h"
#include "DCMotor.h"
#include "PID.h"



DCMotor MotorLeft(9,8), MotorRight(11,10);
PIDClass PIDLeft(2, 0.01, 0, 100), PIDRight(2, 0.01, 0, 100);

uint8_t pwmLeft, pwmRight;

ISR(TIMER0_COMPA_vect){
  nmillis += 10;
  if(counter == time){
    counter = 0;
    activations[0] = recordedInterrupts[0] * 100 / time;
    activations[1] = recordedInterrupts[1] * 100 / time;
    recordedInterrupts[0] = 0;
    recordedInterrupts[1] = 0;
  }
  else{counter++;}
  
}

/*Ultrasound_SensorHCSR04 Sensor;*/

uint32_t distance{0};

void setup(){
  sei();
  Serial.begin(250000);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(11, HIGH);
  
  interruptSetup(0, 2);
  interruptSetup(1, 2);
  timer_setup(100);
  MotorLeft.start();
  MotorRight.start();
  MotorRight.directionset(1);
  MotorLeft.directionset(1);
  MotorRight.speedset(100);
  MotorLeft.speedset(100);
}

void loop(){
  /*distance = Sensor.median();

  Serial.print(",Distance: ");
  Serial.println(distance);*/
  pwmRight = PIDRight.compute(activations[1], 200);
  MotorRight.speedset(pwmRight); //MotorRight
  pwmLeft = PIDLeft.compute(activations[1], 200);
  MotorLeft.speedset(pwmLeft); //MotorRight

  Serial.print(",SpeedR: ");
  Serial.print(activations[1]);
  Serial.print(",PWM: ");
  Serial.println(pwmRight);

  /*Serial.print("Activation 0: ");
  Serial.println(activations[0]*60/49);
  Serial.print("Activation 1: ");
  Serial.println(activations[1]*60/49);*/
  delay(100);
}
