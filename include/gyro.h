#pragma once
#include <arduino.h>
#include "I2CDevice.h"

class Gyro : public I2CDevice
{
  using I2CDevice::I2CDevice;

  public:
    void init();
    int FunctionsPitchRoll(double axisX, double axisY, double axisZ);
    void Functions();
    
  private:
    uint8_t _address;
    int _accelerationX, _accelerationY, _accelerationZ;
};
