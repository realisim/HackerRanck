
#include "BigInt.h"
#include <limits>

using namespace std;

namespace {
  const unsigned int kBase = 1000000000;//numeric_limits<unsigned int>::max();
}


//-------------------------------------
BigInt::BigInt() :
  mPositive(true),
  mData()
{ makeFrom(0); }

//-------------------------------------
BigInt::BigInt(int iV) :
mPositive(true),
mData()
{ makeFrom(iV); }

//-------------------------------------
BigInt::~BigInt()
{}

//-------------------------------------
void BigInt::addToDigit(int iIndex, __uint64_t iV)
{
  if(mData.size() < iIndex + 1)
  { mData.resize(iIndex+1); }
  
  int i = 0;
  while(iV)
  {
    const int nextIndex = iIndex + i;
    
    if( nextIndex < mData.size() )
    {
      iV += mData[nextIndex];
      mData[nextIndex] = iV % kBase;
    }
    else
      mData.push_back(iV % kBase);
    iV /= kBase;
    ++i;
  }
}

//-------------------------------------
void BigInt::makeFrom(int iV)
{
  mPositive = iV >= 0;
  if(!mPositive) { iV *= -1; }
  
  mData = vector<unsigned int>();
  addToDigit(0, iV);
}

//-------------------------------------
BigInt BigInt::operator+(const BigInt& iV)
{
  BigInt r;
  
  int s = max( mData.size(), iV.mData.size() );
  
  for(int i = 0; i < s; ++i)
  {
    const __uint64_t a = i < mData.size() ? mData[i] : 0;
    const __uint64_t b = i < iV.mData.size() ? iV.mData[i] : 0;
    __uint64_t c = a + b;
    
    r.addToDigit(i, c);
  }
  
  return r;
}

//-------------------------------------
BigInt& BigInt::operator+=(const BigInt& iV)
{
  *this = *this + iV;
  return *this;
}

//-------------------------------------
BigInt BigInt::operator*(const BigInt& iV)
{
  BigInt r(0);

  for(size_t i = 0; i < mData.size(); ++i)
  {
    for(size_t j = 0; j < iV.mData.size(); ++j)
    {
      r.addToDigit(i+j, (__uint64_t)mData[i] * (__uint64_t)iV.mData[j]);
    }
  }
  
  return r;
}

//-------------------------------------
// fonctionne uniquement pour les valeurs positives
bool BigInt::operator<(const BigInt& iV)
{
  bool r = false;
  
  if( mData.size() > iV.mData.size() )
  { r = false; }
  else if( mData.size() < iV.mData.size() )
  { r = true; }
  else // equal number of digits
  {
    for(int i = (int)mData.size() - 1; i >= 0 && !r; --i)
    { r = mData[i] < iV.mData[i]; }
  }
    
  return r;
}

//-------------------------------------
bool BigInt::operator==(const BigInt& iV)
{
  bool r = true;
  r &= mPositive == iV.mPositive;
  
  if( mData.size() != iV.mData.size() )
  { r = false; }
  else // equal number of digits
  {
    for(size_t i = 0; i < mData.size() && r; ++i)
    { r &= mData[i] == iV.mData[i]; }
  }
  
  return r;
}

//-------------------------------------
std::string BigInt::toString() const
{
  string r;
  
  int dataIndex = 0;
  for(auto it = mData.rbegin(); it != mData.rend(); ++it, ++dataIndex)
  {
    string r0;
    const int maxDigits = 9; //'99999999' see kBase //numeric_limits<unsigned int>::digits10;
    if( dataIndex > 0)
    {
      r0.resize( maxDigits );
      for(int ii = 0; ii < r0.size(); ++ii )
      { r0[ii] = '0'; }
    }
    
    __uint64_t v = *it;
    int digitIndex = 0;
    while(v > 0)
    {
      if(dataIndex == 0)
      {
        r0 = char(48 + v % 10) + r0;
      }
      else
      {
        r0[ maxDigits - 1 - digitIndex ] = char(48 + v % 10);
      }
      v /= 10;
      
      ++digitIndex;
    }
    
    r += r0;
  }
  
  if(!mPositive){ r = "-" + r; }
  return r;
}

//--- tests
#include <cstdio>
#include <iostream>
#include <string>
void BigInt::tests()
{
  using namespace std;
  {
    BigInt a;
    a.makeFrom(5);
    cout << a.toString() << endl;
    
    a.makeFrom(2046);
    cout << a.toString() << endl;
    
    a.makeFrom(-127);
    cout << a.toString() << endl;
    
  }
  {
    //test addition
    BigInt a(5);
    BigInt b(2);
    cout << (a + b).toString() << endl;
    
    a.makeFrom(5);
    b.makeFrom(6);
    cout << (a + b).toString() << endl;
    
    a.makeFrom(2046);
    b.makeFrom(102046);
    cout << (a + b).toString() << endl;
    
    a.makeFrom(199);
    b.makeFrom(79);
    cout << (a + b).toString() << endl;
  }
  //test multiplication
  {
    BigInt a(5);
    BigInt b(12);
    string r = (a*b) == 60 ? " true" : " false";
    cout << (a * b).toString() << r << endl;
    
    a.makeFrom(25);
    b.makeFrom(4);
    r = (a*b) == 100 ? " true" : " false";
    cout << (a * b).toString() << r << endl;
    
    a.makeFrom(6);
    b.makeFrom(24);
    r = (a*b) == 144 ? " true" : " false";
    cout << (a * b).toString() << r << endl;
    
    a.makeFrom(1024);
    b.makeFrom(1024);
    r = (a*b) == 1048576 ? " true" : " false";
    cout << (a * b).toString() << r << endl;
    
    a.makeFrom(9999999);
    b.makeFrom(99999999);
    r = (a*b) == 999999890000001 ? " true" : " false";
    cout << (a * b).toString() << r << endl;
  }
}
