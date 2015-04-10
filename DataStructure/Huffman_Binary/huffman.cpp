#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include "huffman.h"
#include "binary_tree.h"

using namespace std;


//Encode a character
std::string HuffmanTree::encodeChar(char c)
{
  Node<Data>* pCurr = m_pLeaves[c];
  string ret = "";
  while(pCurr->m_pFa != 0)
  {
    if(pCurr->m_pFa->m_pLc == pCurr)
      ret += '0';
    else if(pCurr->m_pFa->m_pRc == pCurr)
      ret += '1';

    pCurr = pCurr->m_pFa;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

//Decode a character from ASCII
char HuffmanTree::decodeChar(const std::string& input, int& index)
{
  char c = 0;
  Node<Data>* pCurr = m_pRoot;
  while(pCurr->m_data.m_Char == 0)
  {
    if(input[index] == '0')
      pCurr = pCurr->m_pLc;
    else if(input[index] == '1')
      pCurr = pCurr->m_pRc;
    else return 0;
    index++;
  }
  c = pCurr->m_data.m_Char;
  return c;
}

//Build a buffman tree
HuffmanTree::HuffmanTree(const string& input, int freq[sigma])
{
  m_sTemplate = input;
  int sz = input.size();
  fill(freq, freq + sigma, 0);
  for(int i = 0; i < input.size(); i++)
    freq[input[i]]++;


  priority_queue<Node<Data>*, vector<Node<Data>* >, DataComp> q;


  for(int i = 0; i < sigma; i++)
  {
    if(freq[i] != 0)
    {
      Data d(i, freq[i]);
      Node<Data>* pNode = new Node<Data>(d);
      m_pLeaves[i] = pNode;
      q.push(pNode);
    }
  }

  //One Char
  if(q.size() == 1)
  {
    Data d(0, 0);
    m_pRoot = new Node<Data>(d);
    Node<Data>* temp = q.top();
    q.pop();

    m_pRoot->m_pLc = temp;
    temp->m_pFa = m_pRoot;

    return;
  }

  while(q.size() != 1)
  {
    Node<Data>* a = q.top();
    q.pop();
    Node<Data>* b = q.top();
    q.pop();
    Data d(0, a->m_data.m_iFreq + b->m_data.m_iFreq);
    Node<Data>* c = new Node<Data>(d);
    c->m_pLc = a;
    c->m_pRc = b;
    a->m_pFa = c;
    b->m_pFa = c;
    q.push(c);
  }

  m_pRoot = q.top();
  q.pop();
  
  for(int i = 0; i < sigma; i++)
    if(freq[i])
      m_pEncoded[i] = encodeChar(i);
}

//Decode the input
string HuffmanTree::decode(const string& input)
{
  int i = 0;
  int sz = input.size();
  string ret = "";
  while(i < sz)
  {
    ret += decodeChar(input, i);
  }
  return ret;

}

//Return the encoded string where the tree is built
string HuffmanTree::encode()
{
  int sz = m_sTemplate.size();
  string ret = "";
  for(int i = 0; i < sz; i++)
    ret += m_pEncoded[m_sTemplate[i]];
  return ret;
}
