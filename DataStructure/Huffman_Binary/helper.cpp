#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "binary_tree.h"
#include "helper.h"
#include "huffman.h"

using namespace std;

void Helper::biTreePresentation()
{
  //Part 1.
  cout<<"\n";
  cout<<"Part 1. Build a bianry Tree\n";
  cout<<"Input A Line seperated by comma(,):\n";

  //Input String
  string S;
  ifstream ifs("input0");
  if(!ifs)
  {
    cout<<"Error: Cannot open file input0"<<endl;
    return ;
  }
  getline(ifs, S, '\n');
  cout<<"String read is"<<'\n'<<S<<'\n';
  ifs.close();

  //Initialize the binary tree
  Node<char>* biHeap[100<<1];
  BiTree<char> biTree;
  memset(biHeap, 0, sizeof biHeap);
  int curr = 1;
  for(int i = 0; i < S.size(); i++)
  {
      if(S[i] == ',')
      {
        curr++;
        biHeap[curr] = 0;
        continue;
      }
      if(S[i] != ' ')
        biHeap[curr] = new Node<char>(S[i]);
  }


  biTree.initHeap(biHeap, curr);
  cout<<"Leaf node count: "<<biTree.countLeaf()<<'\n';
  cout<<"Degree = 2 count: "<<biTree.countD2()<<'\n';
  cout<<"Height: "<<biTree.height()<<'\n';
  cout<<"Full: "<<(biTree.full()?"YES":"NO")<<'\n';
  cout<<"Releasing space...";

  for(int i = 0; i < (100<<1); i++)
  {
    if(biHeap[i]) delete biHeap[i];
  }

  cout<<"OK"<<endl;
}

void Helper::huffmanTree()
{
  //Part 2
  cout<<'\n';
  cout<<"Part 2. Huffman Tree\n";
  cout<<"Reading String From File (input).............";

  string s, enc, dec, temp;
  ifstream ifs("input");
  if(!ifs)
  {
    cerr<<"Cannot Open FILE input\n"<<endl;
    return; 
  }
  while(!ifs.eof())
  {
    getline(ifs, temp);
    s += temp + '\n';
  }
  ifs.close();

  cout<<"OK\n";
  int freq[sigma];

  HuffmanTree huff(s, freq);

  enc = huff.encode();
  dec = huff.decode(enc);

  cout<<"String read is: \n"<<s<<'\n';
  cout<<"The encoded string (binary) is:\n"<<enc<<"\n\n";
  cout<<"Decoding the string above gets:\n"<<dec<<'\n';
  cout<<"Bits zipped/Bits original = "<<enc.size()<<"/"<<dec.size()*8
  <<"="<<enc.size()/8.0/dec.size()<<'\n';
  cout<<"For more information view output"<<endl;
  cout<<endl;

  //Writing output
  ofstream ofs("output");
  if(!ofs)
  {
    cerr<<"Cannot Open FILE output\n"<<endl;
    return;
  }
  ofs<<"Character\tTimes\tCode"<<'\n';
  for(int i = 0; i < sigma; i++)
  {
    if(freq[i])
    {
      ofs<<"\'";
      if(i == '\n')
        ofs<<"NL"<<"\'\t";
      else
        ofs<<(char)i<<"\'\t";

      ofs<<freq[i]<<"\t";

      ofs<<huff.m_pEncoded[i]<<endl;
    }
  }


}
