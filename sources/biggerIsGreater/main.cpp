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


int t = 0;
vector<string> inputs;

//--------------------------------------------

#define READ_FROM_FILE 1
void readInput()
{
#if READ_FROM_FILE
    ifstream ifs;
    //ifs.open("/Users/po/workGit/hackerRanck/sources/biggerIsGreater/testCases/sample.txt", ios::in);
    ifs.open("/Users/po/workGit/hackerRanck/sources/biggerIsGreater/testCases/input01.txt", ios::in);
    
    ifs >> t;
    inputs.resize(t);
    
    for(int i = 0; i < t; ++i)
    {
        string w;
        ifs >> w;
        inputs[i] = w;
    }
    
#else
    cin >> t;
    inputs.resize(t);
    
    for(int i = 0; i < t; ++i)
    {
        string w;
        cin >> w;
        inputs[i] = w;
    }
#endif
}

void print(const std::vector<string>& iV)
{
    for(auto it : iV)
    {
        cout << it << "\n";
    }
    cout << "\n";
}

// sort all letters and if equals to the input, then
// there is nothing bigger
//
bool isAlreadyTheBiggest(string& iS)
{
    string s = iS;
    
    
    return iS == s;
}

int findFirstLocalMaximum(const string& iS)
{
    assert(iS.size() > 2);
    
    int r = -1;
    
    int i = (int)iS.size() - 1;
    if( iS[i-1] < iS[i] )
        r = i;
    
    for(i = (int)iS.size() - 2; i >= 1 && r == -1; --i)
    {
        if( iS[i-1] < iS[i] && iS[i] >= iS[i+1] )
            r = i;
    }
    
    return r;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    readInput();
 
    for(size_t i = 0; i < inputs.size(); ++i)
    {
        const string& w = inputs[i];
        string s;
        string biggest = w;
        sort(biggest.begin(), biggest.end());
        reverse(biggest.begin(), biggest.end());
        
        // all letters equals, already the biggest -> no answer
        if(biggest == w)
        {
            s = "no answer";
        }
        
        // 2 letters, swap
        else if(w.size() == 2)
        {
            s.resize(2);
            s[0] = w[1];
            s[1] = w[0];
        }
        
        else
        {
            s = w;
            
            // starting from the end (decimals). Find the first
            // local maximum
            int localMaxIndex = findFirstLocalMaximum(w);
            
            // move one left to the local maximum
            int j = localMaxIndex - 1;
            string temp = s;
            string sub = temp.substr(j+1, string::npos);
            
            //find first char greater than temp[j];
            unsigned char g = 255;
            int maxFoundAt = -1;
            for(int k = 0; k < sub.size(); ++k)
            {
                if(sub[k] > temp[j] && sub[k] < g)
                {
                    g = sub[k];
                    maxFoundAt = k;
                }
            }
            
            if(maxFoundAt >= 0)
            {
                sub[maxFoundAt] = temp[j];
                temp[j] = g;
                sort(sub.begin(), sub.end());
                
                temp.replace(j+1, sub.length(), sub);
            }
            
            if(temp > w && (temp < s || s == w))
                s = temp;
        }
        
        //cout << i << ": ";
        cout << s << "\n"; 
    }
    
    return 0;
}
