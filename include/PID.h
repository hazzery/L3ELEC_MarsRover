#pragma once

class PID
{
    
    public:
        //Kp -  Proportional gain.
        //Ki -  Integral gain.
        //Kd -  Derivative gain.
        PID (double kp, double ki, double kd);
        PID ();
        ~PID();

        double calculate(double sensorValue);
        
        //Returns status of PID
        //2 for time out
        //3 if robot is stuck
        //0 for completion
        int status();
        
        //Sets the robot's target distance. 
        void setTarget(double target);
        
        //Sets the PID's start time.
        void start();

        //No clue what its for, but Cory put it in there
        void stop();

        //Resets the private variables
        void resetPID();
        
    
    private:
        const double _Kp;
        const double _Ki;
        const double _Kd;
        const double _min;
        const double _max;
        const double _maxTime;
        const double _maxError;
        const double _integralLimit;
        const double _minDerivative;
        double _target;
        double _error = 11;
        double _pastError;
        double _integral;
        double _derivative = 11;
        double _startTime;
        double _out;
};
