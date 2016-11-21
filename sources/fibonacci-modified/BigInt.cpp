
#include "BigInt.h"

using namespace std;

//-------------------------------------
BigInt::BigInt() :
  mPositive(true),
  mDigits()
{ makeFrom(0); }

//-------------------------------------
BigInt::BigInt(int iV) :
mPositive(true),
mDigits()
{ makeFrom(iV); }

//-------------------------------------
BigInt::~BigInt()
{}

//-------------------------------------
void BigInt::addToDigit(int iIndex, int iV)
{
  if(mDigits.size() < iIndex + 1)
  { mDigits.resize(iIndex+1); }
  
  int i = 0;
  while(iV)
  {
    const int nextIndex = iIndex + i;
    
    if( nextIndex < mDigits.size() )
    {
      iV += mDigits[nextIndex];
      mDigits[nextIndex] = iV%10;
    }
    else
      mDigits.push_back(iV%10);
    iV /= 10;
    ++i;
  }
}

//-------------------------------------
void BigInt::makeFrom(int iV)
{
  mPositive = iV >= 0;
  if(!mPositive) { iV *= -1; }
  
  mDigits = vector<char>();
  mDigits.push_back( iV % 10 );
  iV /= 10;
  while(iV > 0)
  {
    mDigits.push_back( iV % 10 );
    iV /= 10;
  }
}

//-------------------------------------
BigInt BigInt::operator+(const BigInt& iV)
{
  BigInt r;
  
  int s = max( mDigits.size(), iV.mDigits.size() );
  
  for(int i = 0; i < s; ++i)
  {
    const int a = i < mDigits.size() ? mDigits[i] : 0;
    const int b = i < iV.mDigits.size() ? iV.mDigits[i] : 0;
    int c = a + b;
    
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

  for(size_t i = 0; i < mDigits.size(); ++i)
  {
    for(size_t j = 0; j < iV.mDigits.size(); ++j)
    {
      r.addToDigit(i+j, mDigits[i] * iV.mDigits[j]);
    }
  }
  
  return r;
}

//-------------------------------------
// fonctionne uniquement pour les valeurs positives
bool BigInt::operator<(const BigInt& iV)
{
  bool r = false;
  
  if( mDigits.size() > iV.mDigits.size() )
  { r = false; }
  else if( mDigits.size() < iV.mDigits.size() )
  { r = true; }
  else // equal number of digits
  {
    for(int i = (int)mDigits.size() - 1; i >= 0 && !r; --i)
    { r = mDigits[i] < iV.mDigits[i]; }
  }
    
  return r;
}

//-------------------------------------
bool BigInt::operator==(const BigInt& iV)
{
  bool r = true;
  r &= mPositive == iV.mPositive;
  
  if( mDigits.size() != iV.mDigits.size() )
  { r = false; }
  else // equal number of digits
  {
    for(size_t i = 0; i < mDigits.size() && r; ++i)
    { r &= mDigits[i] == iV.mDigits[i]; }
  }
  
  return r;
}

//-------------------------------------
std::string BigInt::toString() const
{
  string r;
  
  r.resize(mDigits.size());
  int i = r.size() - 1;
  for(auto it = mDigits.begin(); it != mDigits.end(); ++it, --i)
  { r[i] = *it + 48; } //48 in the ascci table is character 0
  
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
