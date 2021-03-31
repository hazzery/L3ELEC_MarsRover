#pragma once

class Motor
{
    public:
        Motor(int PinOne, int PinTwo, int PwmPin);

        void drive(short speed);
        void stop();

    private:
        int pinOne, pinTwo, pwmPin;

        void setSpeed(byte speed);
        void setDirection(Direction dir);
};

enum Direction : bool
{
  forwards = true,
  backwards = false,
};