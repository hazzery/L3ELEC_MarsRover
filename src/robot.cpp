#include "../include/robot.h"

Robot::Robot(Motor *left, Motor* right)
:leftDrive(left), rightDrive(right){}

void Robot::drive(short speed)
{
    leftDrive->drive(speed);
    rightDrive->drive(speed);
}

void Robot::turn(short speed)
{
    leftDrive->drive(speed);
    rightDrive->drive(-speed);
}

void Robot::driveFor(float distance)
{

}

void Robot::turnFor(float distance)
{

}