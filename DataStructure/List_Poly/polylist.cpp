/*
 * Author: Allen Ng (1310587)
 * Description: The implementation of class Term and
 * class Term, Polynomial
 * Created on: Mar 11th 2015
 */

#include "polylist.h"
#include <iostream>
#include <cassert>
using namespace std;

// Initialize a new Term
Term::Term(int iCoefficient, int iExponent)
{
  this->m_pNext = 0;
  this->m_iCoefficient = iCoefficient;
  this->m_iExponent = iExponent;
}

// Initialize a `null` Polynomial (not 0)
Polynomial::Polynomial()
{

  m_pHead = new Term(0, 0);
  m_pHead->m_pNext = 0;
  m_pCurr = 0;
  m_iLength = 0;
}


// Insert a term into the polynomial with
// todo: solve duplicate terms
err_t Polynomial::insert(int iCoefficient, int iExponent)
{
  m_pCurr = m_pHead;

  for(;(m_pCurr->m_pNext) != 0 && (m_pCurr->m_pNext->m_iExponent > iExponent);m_pCurr = m_pCurr->m_pNext)
  ;

  Term* newTerm = new Term(iCoefficient, iExponent);
  newTerm->m_pNext = m_pCurr->m_pNext;
  m_pCurr->m_pNext = newTerm;

  m_iLength++;
  return success;

}

// Retrieve the iIndex-th term
err_t Polynomial::retrieve(const int iIndex, Term& term)
{
  if(m_iLength == 0) return notfound;
  if(iIndex >= m_iLength) return outofrange;

  m_pCurr = m_pHead;


  for(int i = 0; i <= iIndex; i++)
    m_pCurr = m_pCurr->m_pNext;

  term = *m_pCurr;

  return success;


}

// Find the term with exponent equals iExponent
err_t Polynomial::find(const int iExponent, Term& term)
{
  if(m_iLength == 0) return notfound;
  m_pCurr = m_pHead->m_pNext;
  while(m_pCurr)
  {
    if(m_pCurr->m_iExponent == iExponent)
    {
      term = *m_pCurr;
      return success;
    }
    m_pCurr = m_pCurr->m_pNext;
  }
  return notfound;
}

// Change the coefficient of the term with exponent equals iExponent to iCoefficient
err_t Polynomial::alter(int iExponent, int iCoefficient)
{
  if(m_iLength == 0) return notfound;
  m_pCurr =  m_pHead->m_pNext;
  while(m_pCurr)
  {
    if(m_pCurr->m_iExponent == iExponent)
    {
      m_pCurr->m_iCoefficient = iCoefficient;
      return success;
    }
    m_pCurr = m_pCurr->m_pNext;
  }
  return notfound;
}

// Update the coefficient and Exponent of the iIndex-th term
err_t Polynomial::update(int iIndex, int iCoefficient, int iExponent)
{
  if(m_iLength == 0) return notfound;
  if(iIndex >= m_iLength) return outofrange;

  m_pCurr = m_pHead;

  for(int i = 0; i <= iIndex; i++)
    m_pCurr = m_pCurr->m_pNext;

  m_pCurr->m_iCoefficient = iCoefficient;
  m_pCurr->m_iExponent = iExponent;

  return success;
}


// Remove the iIndex-th term
err_t Polynomial::remove(int iIndex, Term& term)
{
  if(m_iLength == 0) return notfound;
  if(iIndex >= m_iLength) return outofrange;

  m_pCurr = m_pHead;

  for(int i = 0; i < iIndex; i++)
    m_pCurr = m_pCurr->m_pNext;

  // m_pCurr now points to the element before the iIndex-th term

  term = *(m_pCurr->m_pNext);
  delete m_pCurr->m_pNext;
  m_pCurr->m_pNext = term.m_pNext;
  term.m_pNext = 0;
  m_iLength--;

  return success;
}

// Remove the term with exponent iExponent
err_t Polynomial::removeExp(int iExponent, Term& term)
{
  if(m_iLength == 0) return notfound;

  m_pCurr = m_pHead;
  while(m_pCurr->m_pNext != 0)
  {
    if(m_pCurr->m_pNext->m_iExponent == iExponent)
    {
      term = *(m_pCurr->m_pNext);
      delete m_pCurr->m_pNext;
      m_pCurr->m_pNext = term.m_pNext;
      term.m_pNext = 0;
      m_iLength--;
      return success;
    }
    m_pCurr = m_pCurr->m_pNext;

  }
  return notfound;
}

// Clear the Polynomial and the space it takes up
err_t Polynomial::clear()
{
  if(m_iLength == 0)
  {
    m_pCurr = m_pHead;
    return success;
  }

  m_pCurr = m_pHead->m_pNext;
  while(m_iLength > 0)
  {
    Term* pT = m_pCurr->m_pNext;
    delete m_pCurr;
    m_pCurr = pT;
    m_iLength--;
  }

  m_pCurr= m_pHead;
  m_pHead->m_pNext = 0;
  return success;

}

//Perform Polynomial addition on *this and b
//
err_t Polynomial::add(Polynomial& b)
{
  //
  Term tmp1(0, 0), tmp2(0, 0);
  err_t error = success;

  // Add terms from the second operand into the result
  for(int i = 0; i < b.m_iLength; i++)
  {
    b.retrieve(i, tmp1);
    int tmpErr = this->find(tmp1.m_iExponent, tmp2);

    if(success == tmpErr)
    {
      //will not fail this time
      int iCoefResult = tmp1.m_iCoefficient +
                    tmp2.m_iCoefficient;
      if(iCoefResult)
        alter(tmp1.m_iExponent,
           iCoefResult);
      else
        //delete the term with exponent 0
        removeExp(tmp1.m_iExponent, tmp2);
    }
    else if(notfound == tmpErr)
      insert(tmp1.m_iCoefficient, tmp1.m_iExponent);
    else return tmpErr;
  }
  return success;
}

//Perform Polynomial substraction on *this and b
err_t Polynomial::sub(Polynomial& b)
{
  //
  Term tmp1(0, 0), tmp2(0, 0);
  err_t error = success;

  // Add terms from the second operand into the result
  for(int i = 0; i < b.m_iLength; i++)
  {
    b.retrieve(i, tmp1);
    int tmpErr = this->find(tmp1.m_iExponent, tmp2);

    if(success == tmpErr)
    {
      //will not fail this time
      int iCoefResult = tmp1.m_iCoefficient -
                    tmp2.m_iCoefficient;
      if(iCoefResult)
        alter(tmp1.m_iExponent,
           iCoefResult);
      else
        //delete the term with exponent 0
        removeExp(tmp1.m_iExponent, tmp2);
    }
    else if(notfound == tmpErr)
      insert(-tmp1.m_iCoefficient, tmp1.m_iExponent);
    else return tmpErr;
  }
  return success;
}

// Multiply this and b and store the result in this
err_t Polynomial::multi(Polynomial& b)
{

  Term tmp1(0, 0), tmp2(0, 0);
  err_t error = success;

  Polynomial tmpPoly, tmpResult, res;

  for(int i = 0; i < m_iLength;i++)
  {
    tmpResult.clear();
    //Should never fail
    retrieve(i, tmp1);
    for(int j = 0; j < b.m_iLength; j++)
    {
      assert(b.retrieve(j, tmp2) == 0);

      //Create a polynomial with only one term
      tmpPoly.clear();
      int tmpCoef = tmp1.m_iCoefficient * tmp2.m_iCoefficient;
      int tmpExpo = tmp1.m_iExponent + tmp2.m_iExponent;
      if(tmpCoef != 0)
        tmpPoly.insert(tmpCoef, tmpExpo);

      tmpResult.add(tmpPoly);
    }
    res.add(tmpResult);
  }

  // Copy Back
  this->clear();
  for(int i = 0; i < res.m_iLength;i++)
  {
    res.retrieve(i, tmp1);
    insert(tmp1.m_iCoefficient, tmp1.m_iExponent);
  }
  res.clear();


  return success;
}


//Divide current polynomial by divisor, current polynomial changes to quotient
//And the residual lies in the second parameter
err_t divide(Polynomial& divisor, Polynomial& residual)
{

  return success;
}


//Differentiate current polynomial
err_t Polynomial::diff()
{
  Term tmpTerm(0, 0);
  for(int i = 0; i < m_iLength;i++)
  {
    //This should never fail
    retrieve(i, tmpTerm);
    if(tmpTerm.m_iExponent != 0)
      update(i, tmpTerm.m_iExponent * tmpTerm.m_iCoefficient, tmpTerm.m_iExponent - 1);
    else
      update(i, 0, 0);
  }
  return 0;
}

// release the space
Polynomial::~Polynomial()
{
  clear();
  m_pCurr = 0;
  delete m_pHead;
}
