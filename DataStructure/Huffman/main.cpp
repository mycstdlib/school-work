#include <iostream>
#include <cstdlib>
#include <cstring>
#include "huffman.h"

using namespace std;

int main()
{
  string input;
  cout<<"Input:"<<endl;
  cin>>input;
  HuffmanTree tree;
  Huffman h;
  tree.build(input);
  string out = h.encode(input, tree);

  
  cout<<"Encoded:"<<endl;

  cout<<out<<endl;

  string out2 = h.decode(out, tree);

  cout<<"Decoded:"<<endl;
  cout<<out2<<endl;

  cout<<"Huffman Usage: "<<out.size()<<" bit(s)"<<endl;
  cout<<"Ascii Usage: "<<input.size()*8<<" bit(s)"<<endl;
  cout<<"Ratio: "<<out.size()*100/8.0/input.size()<<"%"<<endl;
  return 0;
}
