#include <iostream>
#include "helper.h"

using namespace std;

//Read a polynomial from an inputstream
void Helper::readpoly(std::istream& ifs, Polynomial& poly)
{
  char c;
  double fCoefficient = 0.0;
  int iExponent = 0;
  while(ifs>>c)
  {
    ifs>>fCoefficient>>c>>iExponent;
    ifs>>c;
    Polynomial temp;
        
    if(iExponent == 0 && fCoefficient == 0)
      return;
    else
    {
      temp.insert(fCoefficient, iExponent);
      poly.add(temp);
    }
  }

}
