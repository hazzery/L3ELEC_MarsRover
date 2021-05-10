#include "../include/motors.h"
#include <arduino.h>

Motor::Motor(int ForwardPin, int BackwardPin, int PwmPin)
:forwardPin(ForwardPin), backwardPin(BackwardPin), pwmPin(PwmPin)
{
    pinMode(forwardPin, OUTPUT);
    pinMode(backwardPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
}

void Motor::setSpeed(uint8_t speed)
{
    analogWrite(pwmPin, speed);
}

void Motor::setDirection(Direction dir)
{
    if(dir == Forwards)
    {
        digitalWrite(forwardPin, HIGH);
        digitalWrite(backwardPin, LOW);
    }
    else
    {
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, HIGH);
    }
}

void Motor::drive(short speed)
{
    if(speed < 0)
        setDirection(Backwards);
    else if(speed > 0)
        setDirection(Forwards);
    else
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
        digitalWrite(forwardPin, HIGH);
        digitalWrite(backwardPin, HIGH);
    }
    else
    {
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, LOW);
    }
}