#ifndef _BINARY_TREE
#define _BINARY_TREE
#define max(A, B) ((A>B)?(A):(B))


template<class T>
class Node
{
public:
  Node<T> *m_pLc, *m_pRc, *m_pFa;
  T m_data;
  Node(T data)
  {
    m_pLc = m_pRc = m_pFa = 0;
    m_data = data;
  }
};

// A class represents a binary tree
template<class T>
class BiTree
{
  int m_iCountLeaf, m_iCountD2, m_iHeight, m_bFull;
  //Calculate the basic information of the Tree
  void dfs(Node<T>* pCurr, int depth)
  {
    m_iHeight = max(depth, m_iHeight);

    char x = 0;

    if(pCurr->m_pLc)
    {
      dfs(pCurr->m_pLc, depth + 1);
      x += 1;
    }

    if(pCurr->m_pRc)
    {
      dfs(pCurr->m_pRc, depth + 1);
      x += 1;
    }

    if(x == 1)  m_bFull = false;
    if(x == 0) m_iCountLeaf++;
    else if(x == 2) m_iCountD2++;

  }

  //initialize the tree with a heap
  void dfs_init(Node<T>* pCurr, int indexHeap, Node<T>** biHeap, int len)
  {

    if((indexHeap << 1) <= len && biHeap[indexHeap<<1])
    {
      pCurr->m_pLc = biHeap[indexHeap<<1];
      pCurr->m_pLc->m_pFa = pCurr;
      dfs_init(pCurr->m_pLc, indexHeap << 1, biHeap, len);
    }

    if((indexHeap << 1 | 1) <= len && biHeap[indexHeap<<1|1])
    {
      pCurr->m_pRc = biHeap[indexHeap<<1|1];
      pCurr->m_pRc->m_pFa = pCurr;
      dfs_init(pCurr->m_pRc, indexHeap << 1 | 1, biHeap, len);
    }

  }

public:
  Node<T> *m_pRoot;
  BiTree()
  {
    m_pRoot = 0;
    m_iCountLeaf = m_iCountD2 = 0;
    m_iHeight = 0;
    m_bFull = true;
  }

  int countLeaf()
  {
    m_iCountLeaf = m_iCountD2 = 0;
    m_iHeight = 0;
    m_bFull = true;
    if(m_pRoot) dfs(m_pRoot, 1);

    return m_iCountLeaf;
  }

  int countD2()
  {
    m_iCountLeaf = m_iCountD2 = 0;
    m_iHeight = 0;
    m_bFull = true;
    if(m_pRoot) dfs(m_pRoot, 1);

    return m_iCountD2;
  }


  int height()
  {
    m_iCountLeaf = m_iCountD2 = 0;
    m_iHeight = 0;
    m_bFull = true;
    if(m_pRoot) dfs(m_pRoot, 1);

    return m_iHeight;
  }
  bool full()
  {
    m_iCountLeaf = m_iCountD2 = 0;
    m_iHeight = 0;
    m_bFull = true;
    if(m_pRoot) dfs(m_pRoot, 1);

    return m_bFull;
  }

  void initHeap(Node<T>** biHeap, int len)
  {
    if(len >= 1 && biHeap[1] != 0)
    {
      m_pRoot = biHeap[1];
      dfs_init(m_pRoot, 1, biHeap, len);
      std::cout<<"ROOT:"<<m_pRoot->m_data<<std::endl;
    }
  }
};
#endif
