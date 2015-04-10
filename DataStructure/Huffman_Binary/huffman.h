#ifndef _HUFFMAN
#define _HUFFMAN
#include <iostream>
#include <cstring>
#include "binary_tree.h"

//Charset 
const int sigma = 256;

//Store the frequency of characters.
class Data
{
public:
  char m_Char;
  int m_iFreq;
  Data() { m_Char = 0; m_iFreq = -1; }
  Data(char ch, int freq): m_Char(ch), m_iFreq(freq)
  {
  }

  bool operator< (const Data& b) const
  {
    return this->m_iFreq < b.m_iFreq;
  }

};

class DataComp
{
public:
  bool operator()(const Node<Data>* a, const Node<Data>* b)
  {
    return !(a->m_data < b->m_data);
  }
};

class HuffmanTree
{

private:
  std::string encodeChar(char);
  char decodeChar(const std::string&, int&);
  void clear(Node<Data>* curr)
  {
    if(curr->m_pLc != 0)
    {
      clear(curr->m_pLc);
      curr->m_pLc = 0;
    }
    if(curr->m_pRc != 0)
    {
      clear(curr->m_pRc);
      curr->m_pRc = 0;
    }
    if(curr->m_pLc == 0 && curr->m_pRc ==0)
      delete curr;
  }
  
public:
  Node<Data>* m_pRoot;
  Node<Data>* m_pLeaves[256];
  std::string m_pEncoded[256];
  std::string m_sTemplate;
  //Build the tree
  HuffmanTree(const std::string&, int[sigma]);
  std::string decode(const std::string&);
  std::string encode();
  ~HuffmanTree()
  {
    clear(m_pRoot);
  }
};

#endif
