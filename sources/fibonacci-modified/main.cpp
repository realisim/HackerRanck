#include "BigInt.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

BigInt fib(int i, vector<BigInt>& iFibs)
{
  if(iFibs[i-2] == -1)
    iFibs[i-2] = fib(i-2, iFibs);
  if(iFibs[i-1] == -1)
    iFibs[i-1] = fib(i-1, iFibs);
    
  iFibs[i] = iFibs[i-2] + iFibs[i-1]*iFibs[i-1];
  return iFibs[i];
}

int main() {
  std::ios::sync_with_stdio(false);
  
  //BigInt::tests();
  
  int t1, t2, n;
  cin >> t1;
  cin >> t2;
  cin >> n;
  
  //ti+2 = ti + (ti+1)^2
  vector<BigInt> fibs(n, -1);
  fibs[0] = t1;
  fibs[1] = t2;
  
  BigInt r = fib(n-1, fibs);
  printf("%s\n", r.toString().c_str());
  
  return 0;
}