#include "../include/gyro.h"
#include <arduino.h>
#include "Wire.h"

Gyro::Gyro(uint8_t Address)
 : address(Address) {}
