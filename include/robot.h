#include "motors.h"
class Robot
{
  public:
    Robot(Motor *left, Motor *right);

    void drive(short speed);
    void turn(short speed);
    
    void driveFor(float distance);
    void turnFor(float distance);

  private:
    Motor *leftDrive;
    Motor *rightDrive;
};
