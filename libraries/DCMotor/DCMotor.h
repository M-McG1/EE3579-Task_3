/** Arduino DC Motor driver v 8.0
 ** Author: Struan Murray
 ** Date: 2018-03-01
 ** Description: Drives a motor using a PWM pin and a direction pin.
 **/

#ifndef DCMOTOR_H_INCLUDED
#define DCMOTOR_H_INCLUDED

#define OFF 0
#define ON  1

#define CLOCKWISE     0
#define ANTICLOCKWISE 1

#define DEFAULTPWMPIN 9
#define DEFAULTDIRPIN 8
#define DEFAULTPWMMIN 0
#define DEFAULTPWMMAX 255

class DCMotor{
private:
    uint8_t pwmPin, dirPin, minpwm, maxpwm, speed;
    bool direction, status;

public:
    DCMotor():

/* This constructor sets the default pwm and direction pins.
 */
        pwmPin{DEFAULTPWMPIN}, dirPin{DEFAULTDIRPIN}, minpwm{DEFAULTPWMMIN},
        maxpwm{DEFAULTPWMMAX}, speed{DEFAULTPWMMIN}, direction{0}, status{0}{

        pinMode(pwmPin, OUTPUT);
        pinMode(dirPin, OUTPUT);
    }

/* This constructor allows you to set different pwm and direction pins.
 */
    DCMotor(uint8_t tempA, uint8_t tempB):
        pwmPin{tempA}, dirPin{tempB}, minpwm{DEFAULTPWMMIN},
        maxpwm{DEFAULTPWMMAX}, speed{DEFAULTPWMMIN}, direction{0}, status{0}{

        pinMode(tempA, OUTPUT);
        pinMode(tempB, OUTPUT);
    }

/* This function starts the motor. It is the ONLY function capable of making the
 * motor move.
 */
    void start(){
        status = ON;
        analogWrite(pwmPin, 255);
        delay(50);
        analogWrite(pwmPin, speed);
    }

/* This function stops the motor. It is also called from directionset if it is
 * set to 0.
 */
    void stop(){
        status = OFF;
        analogWrite(pwmPin, 0);
    }

/* This function sets the direction of the motor. It will immediately update
 * the pins.
 */
    void directionset(bool tempA){

        direction = tempA;

        digitalWrite(dirPin, direction);

        speedset(speed);

        if(status == 1){
            start();
        }
        else{stop();}
    }

/* This function switches the direction of the motor.
 */
    void directionchange(){

        if(direction == CLOCKWISE){directionset(ANTICLOCKWISE);}
        else if(direction == ANTICLOCKWISE){directionset(CLOCKWISE);}
        else{stop();}
        }

/* This function takes in an eight bit value and turn it into a PWM value which
 * is then sent to the motor.
 */
    void speedset(uint8_t tempA){

        speed = map(tempA, 0, 255, minpwm, maxpwm);

        if(status == ON){
            analogWrite(pwmPin, speed);
        }
        else{stop();}
    }

/* This function overrides the minimum pwm of the motor.
 */
    void minimumpwm(uint8_t tempA){
        minpwm = tempA;
        speedset(speed);
    }

/* This function overrides the maximum pwm of the motor.
 */
    void maximumpwm(uint8_t tempA){
        maxpwm = tempA;
        speedset(speed);
    }

    bool ison(){
        return status;
    }
};

#endif // DCMOTOR_H_INCLUDED
