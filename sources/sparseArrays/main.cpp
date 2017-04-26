#include <cmath>
#include <cstdio>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>
#include <map>
using namespace std;

int count(const string& query, const vector<string>& iLookup)
{
    int r = 0;
    for(auto s : iLookup)
    {
        if(s==query){++r;}
    }
    return r;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n = 0, q = 0;
    cin >> n;

    vector<string> strings;
    //number of strings
    for(int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        strings.push_back(s);
    }

    cin >> q;
    vector<string> queries;
    for(int i = 0; i < q; ++i)
    {
        string s;
        cin >> s;
        queries.push_back(s);
    }

    //--- process.

    for(auto query : queries)
    {
        cout << count(query, strings) << "\n";
    }

    return 0;
}
