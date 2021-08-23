#include "../include/PID.h"
#include <arduino.h>

#define sgn(x) (((x) < 0) ? -(x) : (x))

//PID class constructor, sets member variables
PID::PID(double kp, double ki, double kd)
    :_Kp(kp), _Ki(ki), _Kd(kd), _min(-255), _max(255), _maxTime(9999), _maxError(5), _integralLimit(999), _minDerivative(0) {}

PID::PID()
    :PID(0,0,0) {}

//PID calculator function runs PID logic and returns power output
double PID::calculate(double sensorValue)
{   
    _error = _target - sensorValue;
    //Calculate integral (If conditions are met).
    if(abs(_error) > 180)
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

    return output;
}

int PID::status() 
{
    if(millis() - _startTime > _maxTime)
         return 2;  // Time Out
    else if(_derivative < _minDerivative)
         return 3;  // Stuck
    else if (abs(_error) <= _maxError)
        return 0;  // Complete
    else
        return 1;  // Still going
}

void PID::setTarget(double target)
{
    _target = target;
}

void PID::start()
{
    _startTime = millis();
}

void PID::stop()
{
    _out = 0;
}

void PID::resetPID()
{
    _error = 15;
    _pastError = 0;
    _integral = 0;
    _derivative = 0;
}
