#pragma once
#include <arduino.h>

class Gyro
{
    public:
        Gyro();
        Gyro(uint8_t Address);

    private:
        uint8_t address;
};