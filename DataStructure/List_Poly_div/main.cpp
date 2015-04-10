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

int main(int argc, char** argv)
{
  if(argc != 3)
  {
    cerr<<"Usage:\npoly inputfile outputfile"<<endl;
    return -1;
  }
  ifstream ifs(argv[1]);
  ofstream ofs(argv[2]);

  if(!ifs)
  {
    cerr<<"Input File Error"<<endl;
    return -1;
  }
  if(!ofs)
  {
    cerr<<"Output File Error"<<endl;
    return -1;
  }

  Helper h;
  Polynomial a, b, res;

  h.readpoly(ifs, a);
  h.readpoly(ifs, b);

  string operation;
  ifs>>operation;
  operation = operation.substr(0, 3);
  cout<<"Operation:\n";
  cout<<operation<<'\n';

  ifs.close();

  if(operation == "MUL")
    a.multi(b);
  else if(operation == "ADD")
    a.add(b);
  else if(operation == "SUB")
    a.sub(b);
  else if(operation == "DIV")
    a.divide(b, res);
  else if(operation == "DIF")
    a.diff();
  else
    cout<<"Function not Implemented"<<endl;

  cout<<"Result:\n";


  a.write(ofs);
  a.write(cout);
  if(operation == "DIV")
  {
    cout<<"Residual: ";
    res.write(ofs);
    res.write(cout);
  }

  ofs.close();
  return 0;
}
