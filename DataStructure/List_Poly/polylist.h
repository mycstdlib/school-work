/*
 * Author: Allen Ng (1310587)
 * Description: A linear list for polynomial.
 * Created on: Mar 11th 2015
 */
#include <cstring>
#include <iostream>
#include <fstream>

#ifndef _LISTPOLY_H
#define _LISTPOLY_H

//Error code type
enum err_code
{
success = 0,
empty = 1,
overflow = 2,
notfound = 3,
outofrange = 4,
};

typedef int err_t;

//A term of a polynomial (i.e. this represents ax^b)
class Term
{

public:
  int m_iCoefficient;
  int m_iExponent;

public:
  Term *m_pNext;

public:
  Term(int iCoefficient, int iExponent);

  int getCoefficient(){return m_iCoefficient;}
  void setCoefficient(int iCoefficient){m_iCoefficient = iCoefficient;}

  int getExponent(){return m_iExponent;}
  void setExponent(int iExponent){ m_iExponent = iExponent;}

  void write(std::ofstream& ofs, bool first = false)
  {
    if(!first && m_iCoefficient > 0) ofs<<'+';
    if(m_iExponent != 0)
      ofs<<m_iCoefficient<<"x"<<m_iExponent;
    else
      ofs<<m_iCoefficient;
  }
};


//The polynomial implemented by linear list.
//The list maintains the property that, at a certain time, there is exactly no two terms have the same exponent
class Polynomial
{
protected:
  Term *m_pHead, *m_pCurr;
  int m_iLength;

public:
  Polynomial();
  err_t insert(int, int);
  err_t retrieve(const int, Term&);
  err_t find(const int, Term&);
  err_t alter(int, int);
  err_t update(int, int, int);
  err_t remove(int, Term&);
  err_t removeExp(int, Term&);
  err_t clear();
  
  err_t add(Polynomial&);
  err_t sub(Polynomial&);
  err_t multi(Polynomial&);
  err_t divide(Polynomial&, Polynomial&);
  err_t diff();
  
  ~Polynomial();

  // out put the link to the file
  void write(std::ofstream& ofs)
  {
    if(m_iLength == 0)
    {
      ofs<<'0'<<std::endl;
      return;
    }
    m_pCurr = m_pHead->m_pNext;
    m_pCurr->write(ofs, true);
    while(m_pCurr->m_pNext != 0)
    {
      m_pCurr = m_pCurr->m_pNext;
      m_pCurr->write(ofs);
    }
    ofs<<std::endl;
  }
};

#endif
