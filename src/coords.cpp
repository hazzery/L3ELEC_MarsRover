#include "../include/coords.h"
#include "../include/units.h"
#include <arduino.h>

Coords::Coords(double lat, double lon)
  :lattitude(lat), longitude(lon){}
    
double Coords::getLat(AngleUnits angleUnit = radians) const
{ 
  if (angleUnit == radians)
    return lattitude;
  else
    return lattitude * RAD_TO_DEG;
}

double Coords::getLon(AngleUnits angleUnit = radians) const
{ 
  if (angleUnit == radians)
    return longitude;
  else
    return longitude * RAD_TO_DEG;
}

double Coords::getDistance(Coords a, Coords b, DistanceUnits distanceUnit = m) const
{
  const int earthRadius = 6371000;
 
  //This portion calculates the differences for the Radian latitudes and longitudes and saves them to variables
  double diffLon = b.getLon() - a.getLon();
  double diffLat = b.getLat() - a.getLat();
 
  //This portion is the Haversine Formula for distance between two points. Returned value is in KM
  double angle = (sq(sin(diffLat/2))) + cos(a.getLat()) * cos(b.getLat()) * (sq(sin(diffLon/2)));
  double E = 2 * atan2(sqrt(angle), sqrt(1-angle)) ;
  double distance = (earthRadius * E);

  return distance / pow(10, (int)distanceUnit);
}

double Coords::getBearing(Coords a, Coords b, AngleUnits angleUnit = radians) const
{
  double diffLon = abs(a.getLon() - b.getLon());

  double x = cos(a.getLat()) * sin(diffLon);

  double y = cos(a.getLat()) * sin(b.getLat()) - sin(a.getLat()) * cos(b.getLat()) * cos(diffLon);

  double bearing = atan2(y, x);

  if (angleUnit == radians)
    return bearing;
  else
    return bearing * RAD_TO_DEG;
}
