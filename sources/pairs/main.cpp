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
#include <cassert>
using namespace std;

//
//https://www.hackerrank.com/challenges/pairs
//

int n = 0;
int k = 0;
vector<uint32_t> inputs;

//--------------------------------------------

#define READ_FROM_FILE 1
void readInput()
{
#if READ_FROM_FILE
    ifstream ifs;
    ifs.open("/Users/po/workGit/hackerRanck/sources/pairs/testCases/sample.txt", ios::in);
    
    ifs >> n;
    ifs >> k;
    inputs.resize(n);
    
    for(int i = 0; i < n; ++i)
    {
        uint32_t v;
        ifs >> v;
        inputs[i] = v;
    }
    
#else
    cin >> n;
    cin >> k;
    inputs.resize(n);
    
    for(int i = 0; i < n; ++i)
    {
        uint32_t v;
        cin >> v;
        inputs[i] = v;
    }
#endif
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    readInput();
    
    sort(inputs.begin(), inputs.end());
 
    //vector< pair<uint32_t, uint32_t> > pairs;
    
    int count = 0;
    for(size_t i = 0; i < inputs.size(); ++i)
    {
        const int a = inputs[i];
        int v = std::numeric_limits<uint32_t>::max();
        for(size_t j = i; j < inputs.size() && v <= k; ++j)
        {
            const int b = inputs[j];
            v = abs(a-b);
            if(v == k)
            {
                count++;
            }
        }
    }
    
    cout << count;
    return 0;
}
