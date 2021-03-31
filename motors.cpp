#include "motors.h"

Motor::Motor(int PinOne, int PinTwo, int PwmPin)
:pinOne(PinOne), pinTwo(PinTwo), pwmPin(PwmPin) {}

void Motor::setSpeed(byte speed)
{

}
void Motor::setDirection(Direction dir)
{

}

void Motor::drive(short speed)
{
    if(speed < 0)
        setDirection(backwards);
    else if(speed > 0)
        setDirection(forwards);
    else
    {
        stop();
        return;
    }
    setSpeed(abs(speed));

}
void Motor::stop()
{

}