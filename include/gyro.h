#pragma once
#include <arduino.h>
#include "I2CDevice.h"

class Gyro : public I2CDevice
{
  using I2CDevice::I2CDevice;

  private:
    uint8_t address;

    int AcX, AcY, AcZ;

  public:
    void init();
    int FunctionsPitchRoll(double A, double B, double C);
    void Functions();
};