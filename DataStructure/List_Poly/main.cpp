/*
* Author: Allen Ng (1310587)
* Description: Demo
* Created on: Mar 12th 2015
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include "helper.h"
#include "polylist.h"

using namespace std;

int main()
{
  ifstream ifs("inputfile.txt");
  ofstream ofs("outputfile.txt");
  if(!ifs)
    cerr<<"File Read Error"<<endl;

  Helper h;
  Polynomial a, b;

  h.readpoly(ifs, a);
  h.readpoly(ifs, b);

  string operation;
  ifs>>operation;
  operation = operation.substr(0, 3);
  cout<<operation<<endl;

  ifs.close();

  if(operation == "MUL")
  {
    a.multi(b);
  }
  else if(operation == "AND")
  {
    a.add(b);
  }
  else if(operation == "SUB")
  {
    a.sub(b);
  }
  else
  {
    cout<<"Function not Implemented"<<endl;
  }


  a.write(ofs);
  return 0;
}
