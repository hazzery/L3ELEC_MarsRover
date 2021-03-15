#include "coords.h"
Coords::Coords(double lat, double lon)
    :lattitude(lat), longitude(lon){}
    
double Coords::getLat()
{ return lattitude; }
double Coords::getLon()
{ return longitude; }
