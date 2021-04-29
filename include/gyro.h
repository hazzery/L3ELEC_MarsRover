#pragma once
#include <arduino.h>

class Gyro
{
    public:
        Gyro();
        Gyro(uint8_t Address);

        void init();
        int FunctionsPitchRoll(double A, double B, double C);
        void Functions();

    private:
        uint8_t address;
};