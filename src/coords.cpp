#define DISABLE_PREDEFINED_UNITS
#define ENABLE_PREDEFINED_LENGTH_UNITS
#define ENABLE_PREDEFINED_ANGLE_UNITS

#include "../include/coords.h"
#include "../include/units.h"
// #include <arduino.h>

using namespace units::length;
using namespace units::angle;


Coords::Coords(radian_t lat, radian_t lon)
  :lattitude(lat), longitude(lon){}
  
Coords::Coords(degree_t lat, degree_t lon)
  :lattitude(lat), longitude(lon){}

template<typename angleUnit>
angleUnit Coords::getLat()
{ 
  return lattitude;
}
template<typename angleUnit>
angleUnit Coords::getLon()
{ 
  return longitude;
}
template<typename distanceUnit>
distanceUnit Coords::getDistance(Coords a, Coords b)
{
  const meter_t earthRadius = 6371000;
 
  //This portion calculates the differences for the Radian latitudes and longitudes and saves them to variables
  radian_t diffLon = b.getLon() - a.getLon();
  radian_t diffLat = b.getLat() - a.getLat();
 
  //This portion is the Haversine Formula for distance between two points. Returned value is in KM
  raidian_t angle = (math::sq(math::sin(diffLat/2))) + math::cos(a.getLat()) * math::cos(b.getLat()) * (math::sq(math::sin(diffLon/2)));
  double E = 2 * atan2(sqrt(angle), sqrt(1-angle)) ;
  distanceUnit distance = (earthRadius * E);

  return distance;
}
template<typename angleUnit>
angleUnit Coords::getBearing(Coords a, Coords b)
{
  angleUnit diffLon = math::abs(a.getLon() - b.getLon());

  angleUnit x = math::cos(a.getLat()) * math::sin(diffLon);

  angleUnit y = math::cos(a.getLat()) * math::sin(b.getLat()) - math::sin(a.getLat()) * math::cos(b.getLat()) * math::cos(diffLon);

  angleUnit bearing = math::atan2(y, x);

  return bearing;
}
