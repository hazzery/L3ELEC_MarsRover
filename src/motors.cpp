#include "../include/motors.h"
#include <arduino.h>

Motor::Motor(int ForwardPin, int BackwardPin, int PwmPin)
:forwardPin(ForwardPin), backwardPin(BackwardPin), pwmPin(PwmPin)
{
    //Set our 3 pins to output mode so that we can write to them.
    pinMode(forwardPin, OUTPUT);
    pinMode(backwardPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
}

void Motor::setSpeed(uint8_t speed)
{
    analogWrite(pwmPin, speed);//PWM voltage to control speed of motors
}

void Motor::setDirection(Direction dir)
{
    if(dir == Forwards)
    {
        digitalWrite(forwardPin, HIGH);//In1 high...
        digitalWrite(backwardPin, LOW);//...and In2 low makes motors go forward.
    }
    else
    {
        digitalWrite(forwardPin, LOW);//In1 low...
        digitalWrite(backwardPin, HIGH);//...and In2 high makes motors reverse.
    }
}

void Motor::drive(short speed)
{
    if(speed < 0)
        setDirection(Backwards);
    else if(speed > 0)
        setDirection(Forwards);
    else //If speed is 0.
    {
        stop();
        return;
    }
    setSpeed(abs(speed));
}

void Motor::stop(BrakeMode mode = Coast)
{
    if(mode == Coast)
    {
        setSpeed(0);//Setting speed to 0 "disengages" motor
    }
    else
    {
        setSpeed(255);//Lock on the break (we don't want ABS)
        digitalWrite(forwardPin, LOW);//Seting both In1...
        digitalWrite(backwardPin, LOW);//...and In2 to same value shorts the motors, applying a brake.
    }
}