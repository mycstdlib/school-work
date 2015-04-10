#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include <iostream>
#include <queue>
#include <cstring>

const int sigma = 256;
class Node
{
public:
  int weight;
  char code;
  int lc, rc, index, fa;
  bool operator<(const Node& b) const
  {
    return weight > b.weight;
  }
};
class HuffmanTree
{
private:

  int pos[sigma];
  Node* binary_tree;
  int m_pRoot;
public:
  HuffmanTree();
  void build(const std::string&);
  void clear();
  std::string encodeChar(char) const;
  char decodeChar(const std::string&, int& start) const;
  ~HuffmanTree();
};
class Huffman
{
public:
  std::string encode(const std::string&, const HuffmanTree&);
  std::string decode(const std::string&, const HuffmanTree&);

};


#endif
