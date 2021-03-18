#pragma once

class Coords
{
  private:
    double lattitude, longitude;
    
  public:
    Coords(double lat, double lon);
    
    double getLat(bool rad);
    double getLon(bool rad);
};