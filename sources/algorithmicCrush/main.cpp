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
    unsigned long long int k;
};

int n = 0, m = 0;
vector<operation> operations;

//--------------------------------------------

#define READ_FROM_FILE 1
void readInput()
{
#ifdef READ_FROM_FILE
    ifstream ifs;
    ifs.open("/Users/po/workGit/hackerRanck/sources/algorithmicCrush/testCases/input10.txt", ios::in);

    ifs >> n >> m;
    
    for(int i = 0; i < m; ++i)
    {
        operation o;
        ifs >> o.a >> o.b >> o.k;
        operations.push_back(o);
    }

#elif
    cin >> n >> m;
    
    for(int i = 0; i < m; ++i)
    {
        operation o;
        cin >> o.a >> o.b >> o.k;
        operations.push_back(o);
    }
#endif
}

void printOperationResult(const map<int, unsigned long long int>& iMap)
{
    for(auto it : iMap)
    {
        cout << it.first << " " << it.second << "\n";
    }
    cout << "\n";
}

void insert(int i, map<int, unsigned long long int>& iMap)
{
    // increment all values in betwen
    auto itI = iMap.find(i);
    
    if(itI == iMap.end())
    {
        iMap[i] = 0;
        itI = iMap.find(i);
        if(i > 0)
        {
            auto previousV = itI;
            previousV--;
            iMap[i] = previousV->second;
        }
        
        if(i < n)
        {
            auto nextV = itI;
            nextV++;
            iMap[i+1] = nextV->second;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    readInput();
    
    unsigned long long int maxValue = 0;
    map<int, unsigned long long int> values;
    values[0] = 0;
    values[n-1] = 0;
    
    for(auto o : operations)
    {
        const int i = o.a - 1;
        const int j = o.b - 1;
        
        insert(i, values);
        insert(j, values);

        auto itI = values.find(i);
        auto itJ = values.find(j);
        for(; itI != itJ; ++itI )
        {
            itI->second += o.k;
            maxValue = max(maxValue, itI->second);
        }
        itI->second += o.k;
        maxValue = max(maxValue, itI->second);
        
        printOperationResult(values);
    }
    
    cout << maxValue;
    return 0;
}
