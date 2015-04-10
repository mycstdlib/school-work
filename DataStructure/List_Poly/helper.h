/*
 * Author: Allen Ng (1310587)
 * Description: A helper class that helps readpolygon.
 * Created on: Mar 11th 2015
 */
 #include <iostream>
#include <fstream>
#include "polylist.h"

#ifndef _HELPER_H
#define _HELPER_H

class Helper
{
public:
  void readpoly(std::ifstream& , Polynomial&);
};

#endif
