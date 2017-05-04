#include <cmath>
#include <cstdio>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>
using namespace std;

struct operation
{
    int a;
    int b;
    long long k;
};

int n = 0, m = 0;
vector<operation> operations;

//--------------------------------------------

#define READ_FROM_FILE 0
void readInput()
{
#if READ_FROM_FILE
    ifstream ifs;
    ifs.open("/Users/po/workGit/hackerRanck/sources/algorithmicCrush/testCases/input10.txt", ios::in);
    
    ifs >> n >> m;
    
    for(int i = 0; i < m; ++i)
    {
        operation o;
        ifs >> o.a >> o.b >> o.k;
        operations.push_back(o);
    }
    
#else
    cin >> n >> m;
    
    for(int i = 0; i < m; ++i)
    {
        operation o;
        cin >> o.a >> o.b >> o.k;
        operations.push_back(o);
    }
#endif
}

void printOperationResult(const std::vector<long long>& iValues)
{
    for(auto it : iValues)
    {
        cout << it << " ";
    }
    cout << "\n";
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    readInput();
    
    long long maxValue = 0;
    vector<long long> impulsions;
    impulsions.resize(n, 0);
    
    for(auto o : operations)
    {
        const int i = o.a - 1;
        const int j = o.b - 1;
        
        impulsions[i] += o.k;
        if( (j+1) < n )
        {
            impulsions[j+1] -= o.k;
        }
        
        //printOperationResult(impulsions);
    }
    
    long long x = 0;
    for(auto i : impulsions)
    {
        x += i;
        maxValue = std::max(maxValue, x);
    }
    
    cout << maxValue;
    return 0;
}
