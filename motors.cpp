#include "motors.h"

Motor::Motor(int PinOne, int PinTwo, int PwmPin)
:pinOne(PinOne), pinTwo(PinTwo), pwmPin(PwmPin)
{
    pinMode(pinOne, OUTPUT);
    pinMode(pinTwo, OUTPUT);
    pinMode(pwmPin, OUTPUT);
}

void Motor::setSpeed(byte speed)
{
    analogWrite(pwmPin, speed);
}
void Motor::setDirection(Direction dir)
{
    if(dir == Forwards)
    {
        digitalWrite(pinOne, LOW);
        digitalWrite(pinTwo, HIGH);
    }
    else
    {
        digitalWrite(pinOne, HIGH);
        digitalWrite(pinTwo, LOW);
    }
}

void Motor::drive(char speed)
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
        digitalWrite(pinOne, HIGH);
        digitalWrite(pinTwo, HIGH);
    }
    else
    {
        digitalWrite(pinOne, LOW);
        digitalWrite(pinTwo, LOW);
    }
}