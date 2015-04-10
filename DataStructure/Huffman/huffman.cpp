#include <queue>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "huffman.h"

using namespace std;

HuffmanTree::HuffmanTree()
{
  binary_tree = 0;
  m_pRoot = -1;
  fill(pos, pos + sigma, -1);
}

void HuffmanTree::build(const std::string& sInput)
{
  clear();
  int freq[sigma];
  size_t sz = sInput.size();
  fill(freq, freq + sigma, 0);

  for(int i = 0; i < sz; i++)
    freq[sInput[i]]++;

  priority_queue<Node> q;
    
  int pCurr = 0, alphabet = 0;

  for(int i = 0; i < sigma; i++)
    if(freq[i] != 0) alphabet++;

  
  if(alphabet == 1)
  {
    pos[sInput[0]] = 0;
    binary_tree = new Node[2];
    binary_tree[0].code = sInput[0];
    binary_tree[0].index = 0;
    binary_tree[0].weight = 1;
    binary_tree[0].lc = binary_tree[0].rc = -1;
    binary_tree[0].fa = 1;
    binary_tree[1].lc = 0;
    binary_tree[1].rc = -1;
    binary_tree[1].code = 0;
    binary_tree[1].index = 1;
    binary_tree[1].fa = -1;
    return ;
  }

  binary_tree = new Node[2*alphabet - 1];
  
  for(int i = 0; i < sigma; i++)
  {
    if(freq[i] != 0)
    {
      Node& curr = binary_tree[pCurr];
      curr.weight = freq[i];
      curr.code = i;
      curr.index = pCurr;
      curr.lc = curr.rc = -1;
      curr.fa = -1;
      q.push(curr);
      pos[i] = pCurr;
      pCurr++;
    }
  }
  while(q.size() != 1)//should be sz - 1
  {
    Node a = q.top();
    q.pop();
    Node b = q.top();
    q.pop();

    Node& c = binary_tree[pCurr];
    c.weight = a.weight + b.weight;
    c.code = 0;
    c.lc = a.index;
    c.rc = b.index;
    c.index = pCurr;
    c.fa = -1;

    binary_tree[a.index].fa = pCurr;
    binary_tree[b.index].fa = pCurr;

    pCurr++;
    q.push(c);

  }

  m_pRoot = q.top().index;
  q.pop();
  cout<<pCurr<<endl;

  cout<<"build finished"<<endl;

}

char HuffmanTree::decodeChar(const std::string& sInput, int& start) const
{
  int curr = m_pRoot;
  while(binary_tree[curr].code == 0)
  {
    if(sInput[start] == '0')
    {
      curr = binary_tree[curr].lc;
    }
    else
    {
      curr = binary_tree[curr].rc;
    }
    start++;
  }
  start --;
  return binary_tree[curr].code;
}

void HuffmanTree::clear()
{
  delete [] binary_tree;
}

std::string HuffmanTree::encodeChar(char c) const
{
  int last = pos[c];
  int p = binary_tree[last].fa;
  string res = "";
  while(p != -1)
  {
    if(binary_tree[p].lc == last)
      res += '0';
    else
      res += '1';

    last = p;
    p = binary_tree[p].fa;
  }
  reverse(res.begin(), res.end());

  return res;
}

HuffmanTree::~HuffmanTree()
{
  clear();
}

std::string Huffman::encode(const std::string& sInput, const HuffmanTree& hufft)
{
  cout<<"encode start"<<endl;
  string res;
  int sz = sInput.size();
  for(int i = 0; i < sz; i++)
  {
    res += hufft.encodeChar(sInput[i]);
  }
  return res;
}

std::string Huffman::decode(const std::string& sInput, const HuffmanTree& hufft)
{
  string res;
  int i = 0;
  while(i != sInput.size())
  {
    res += hufft.decodeChar(sInput, i);
    i++;
  }
  return res;
  
}
