#ifndef _BINARYTREE_H
#define _BIANRYTREE_H

template<class T>
class Node
{
  T m_data;
  Node* m_pLc, * m_pRc, * m_pFa;
};

template<class T>
class BinaryTree
{
public:
  Node<T>* m_pRoot;

  BinaryTree()
  {
    m_pRoot = 0;
  }

  void traverse();
  int countLeave();
  int height();
  bool full();
};

#endif
