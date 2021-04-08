#include "../include/PID.h"
#include <arduino.h>

short sgn(double n)
{
    if (n > 0)
        return 1;
    else if (n = 0)
        return 0;
    else if (n < 0)
        return -1;
}

//PID class constructor, sets member variables
PID::PID(double kp, double ki, double kd)
    :_Kp(kp), _Ki(ki), _Kd(kd), _min(-12000), _max(12000), _maxTime(9999), _maxError(5), _integralLimit(9999), _minDerivative(0) {}

PID::PID()
    :_Kp(0), _Ki(0), _Kd(0), _min(0), _max(0), _maxTime(9999), _maxError(10),  _integralLimit(9999), _minDerivative(10) {}

PID::~PID() {}

//PID calculator function runs PID logic and returns power output
void PID::calculate(double sensorVal)
{
    _error = _target - sensorVal;//Calculate error.
    
    //Calculate integral (If conditions are met).
    if(abs(_error) > 750)
        _integral = 0;
    else if (_error == 0)
        _integral = 0;
    else if(abs(_integral) > _integralLimit)
        _integral = _integralLimit * sgn(_integral);
    else
        _integral += _error;
    
    _derivative = _error - _pastError;//Calculate derivative.
    
    //Calculate PID values.
    double pOut = _Kp * _error;
    double iOut = _Ki * _integral;
    double dOut = _Kd * _derivative;
    
    double output = pOut + iOut + dOut;//Calculate Output.
    
    //Restrict output to max/min.
    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;
    
    //Save previous error.
    _pastError = _error;

    _out = output;
}

bool PID::done() 
{
    // if(millis() - _startTime > _maxTime)
    //     return true;
    // else if(_derivative < _minDerivative)
    //     return true;
    if (abs(_error) <= _maxError)
        return true;
    else
        return false;
}

double PID::calculateError(double sensorVal)
{
    _error = _target - sensorVal;//Calculate error.
    return _error;
}

void PID::setTarget(double target)
{
    _target = target;
}

void PID::startTimer()
{
    _startTime = millis();
}

void PID::resetPID()
{
    _error = 15;
    _pastError = 0;
    _integral = 0;
    _derivative = 0;
}

double PID::output()
{ return _out; }
