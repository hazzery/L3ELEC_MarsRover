#pragma once

#include <arduino.h>

enum Direction : bool
{
  Forwards = true,
  Backwards = false,
};
enum BrakeMode : bool
{
  Brake = true,
  Coast = false,
};

class Motor
{
  public:
    Motor(int ForwardPin, int backwardPin, int PwmPin);

      void drive(short speed);
      void stop(BrakeMode mode = Coast);
      void setSpeed(uint8_t speed);
      void setDirection(Direction dir);

  private:
    int forwardPin, backwardPin, pwmPin;

};
