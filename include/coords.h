#pragma once

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_PREDEFINED_LENGTH_UNITS
#define ENABLE_PREDEFINED_ANGLE_UNITS

#include "units.h"

using namespace units::length;
using namespace units::angle;

class Coords
{
  private:
    radian_t lattitude, longitude;
    
  public:
    //lat - Lattitudinal angle
    //lon - Longitudinal angle
    Coords(radian_t lat, radian_t lon);
    Coords(degree_t lat, degree_t lon);

    template<typename angleUnit> angleUnit getLat();
    template<typename angleUnit> angleUnit getLon();
    
    template<typename distanceUnit> static distanceUnit getDistance(Coords a, Coords b);
    template<typename angleUnit> static angleUnit  getBearing(Coords a, Coords b);
};
