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