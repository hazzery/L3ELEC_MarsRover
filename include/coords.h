#pragma once
#include "units.h"

class Coords
{
  private:
    double lattitude, longitude;
    
  public:
    //lat - Lattitudinal angle
    //lon - Longitudinal angle
    //units are interpreted as radians.
    //Use _deg to convert degrees.
    Coords(double lat, double lon);

    double getLat(AngleUnits angleUnit) const;
    double getLon(AngleUnits angleUnit) const;
    
    static double getDistance(Coords a, Coords b, DistanceUnits distanceUnit = m);
    static double getBearing(Coords a, Coords b, AngleUnits angleUnit = radians);
};
