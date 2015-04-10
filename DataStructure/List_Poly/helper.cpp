#include "helper.h"
#include <fstream>

using namespace std;

//Read a polynomial from an inputstream
void Helper::readpoly(std::ifstream& ifs, Polynomial& poly)
{
  char c;
  while(ifs>>c)
  {
    int iCoefficient = 0, iExponent = 0;
    ifs>>iCoefficient>>c>>iExponent;
    ifs>>c;
        
    if(iExponent == 0 && iCoefficient == 0)
      return;
    else
      poly.insert(iCoefficient, iExponent);
  }

}
