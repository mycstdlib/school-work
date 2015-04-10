#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "binary_tree.h"
#include "huffman.h"
#include "helper.h"

using namespace std;




int main()
{
  Helper helper;
  while(1)
  {
    cout<<"-----------------------------";
    cout<<"--------------\n";
    cout<<"Select Function:"<<'\n';
    cout<<"1. Binary Tree Presentation\n";
    cout<<"2. Huffman Tree\n";
    cout<<"3. Quit\n";
    
    int op;
    cin>>op;
    if(op == 1)
      helper.biTreePresentation();
    else if(op == 2)
      helper.huffmanTree();
    else if(op == 3)
      break;
    else
      cout<<"Invalid Number"<<endl;
  }
  return 0;

}
