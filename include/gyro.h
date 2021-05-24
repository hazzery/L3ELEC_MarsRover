#pragma once
#include <arduino.h>
#include "I2CDevice.h"

class Gyro : public I2CDevice
{
  using I2CDevice::I2CDevice;
  using I2CDevice::writeToRegistery;

  public:
    void init();
    int FunctionsPitchRoll(double axisX, double axisY, double axisZ);
    void Functions();
    
  private:
    int _accelerationX, _accelerationY, _accelerationZ;
};
