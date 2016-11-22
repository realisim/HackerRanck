
#include <string>
#include <vector>

class BigInt
{
public:
  BigInt();
  BigInt(int);
  BigInt(const BigInt& ) = default;
  BigInt& operator=(const BigInt&) = default;
  ~BigInt();
  
  BigInt operator+(const BigInt&);
  BigInt& operator+=(const BigInt&);
  //BigInt operator-(const BigInt&);
  //BigInt operator-=(const BigInt&);
  BigInt operator*(const BigInt&);
  //BigInt operator*=(const BigInt&);
//  BigInt operator/(const BigInt&);
//  BigInt operator/=(const BigInt&);
  bool operator<(const BigInt&);
  bool operator==(const BigInt&);
  void makeFrom(int);
  static void tests();
  std::string toString() const;
  
  
private:
  void addToDigit(int iIndex, __uint64_t iV);
  
  bool mPositive;
  std::vector<unsigned int> mData;
};