#include "coords.h"

Coords::Coords(double lat, double lon)
  :lattitude(lat), longitude(lon){}
    
double Coords::getLat(bool rad = true)
{ 
  if (rad)
      return lattitude * (3.141592653589793238 / 180);
  else
      return lattitude;
}
double Coords::getLon(bool rad = true)
{ 
  if (rad)
      return longitude * (3.141592653589793238 / 180);
  else
      return longitude;
}
double Coords::getDistance(Coords a, Coords b)
{
  const int earthRadius = 6371;
 
  //This portion calculates the differences for the Radian latitudes and longitudes and saves them to variables
  double diffLon = b.getLon() - a.getLon();
  double diffLat = b.getLat() - a.getLat();
 
  //This portion is the Haversine Formula for distance between two points. Returned value is in KM
  double angle = (sq(sin(diffLat/2))) + cos(a.getLat()) * cos(b.getLat()) * (sq(sin(diffLon/2)));
  double E = 2 * atan2(sqrt(angle), sqrt(1-angle)) ;
  double distance = earthRadius * E;

  return distance;
}
double Coords::getBearing(Coords a, Coords b)
{
  double diffLon = abs(a.getLon() - b.getLon());

  double x = cos(a.getLat()) * sin(diffLon);

  double y = cos(a.getLat()) * sin(b.getLat()) - sin(a.getLat()) * cos(b.getLat()) * cos(diffLon);

  double bearing = atan2(y, x);

  return bearing;
}