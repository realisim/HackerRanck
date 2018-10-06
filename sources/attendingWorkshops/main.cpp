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
#include <set>
#include <cassert>
using namespace std;

//----
#include "Timer.h"
//----
//
//https://www.hackerrank.com/challenges/attending-workshops/problem
//


//Define the structs Workshops and Available_Workshops.
struct Workshop
{
    Workshop() {}
    
    bool operator<(const Workshop &iRhs) const
    {        
        return mEnd < iRhs.mEnd;
    }
    
    int mStart;
    int mEnd;
    int mDuration;
    
    bool mMarkedAsRemoved;
} ;

struct Available_Workshops
{
    Available_Workshops() {}
    
    vector<Workshop> mWorkshops;
};

//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize(int *pStartTimes, int *pDuration, int n)
{
    realisim::utils::Timer _t;
    
    Available_Workshops *r = new Available_Workshops();
    for(int i = 0; i < n; ++i)
    {
        Workshop w;
        w.mStart = pStartTimes[i];
        w.mDuration = pDuration[i];
        w.mEnd = w.mStart + w.mDuration;
        w.mMarkedAsRemoved = false;
        r->mWorkshops.push_back(w);
    }
    
    printf("initialize: %f\n", _t.getElapsed());
    return r;
}

int CalculateMaxWorkshops(Available_Workshops *ipAw)
{
    realisim::utils::Timer _t;
    int r = 0;
    
    // sort by start time/duration;
    sort(ipAw->mWorkshops.begin(), ipAw->mWorkshops.end());
    
    printf("sort: %f\n", _t.getElapsed());
    _t.start();
    
    // print workshop
    /*for(auto w : ipAw->mWorkshops)
    {
        cout << w.mStart << "|" << w.mDuration << "|" << w.mEnd << " ";
    }
    cout<<endl;*/
    
    //try all
    vector<Workshop> attending; 
    
    auto mainIt = ipAw->mWorkshops.begin();
    while(mainIt != ipAw->mWorkshops.end())
    {
        if(!mainIt->mMarkedAsRemoved)
        {
            // pick earliest end time
            Workshop earliestEndTime = *mainIt;
            attending.push_back( earliestEndTime );
            
            //remove all intersecting
            auto it = mainIt;
            for(; it != ipAw->mWorkshops.end(); ++it)
            {
                const bool notIntersecting =
                (it->mStart <= earliestEndTime.mStart &&
                 it->mEnd <= earliestEndTime.mStart) ||
                (it->mStart >= earliestEndTime.mEnd &&
                 it->mEnd >= earliestEndTime.mEnd);
                
                const bool isIntersecting = !notIntersecting;
                
                if(isIntersecting)
                {
                    it->mMarkedAsRemoved = true;
                }
                
            }
        }
        mainIt++;
    }
    
    printf("work: %f\n", _t.getElapsed());
    _t.start();
    
    /*for(auto w : attending)
    {
        cout << w.mStart << "|" << w.mDuration << "|" << w.mEnd << " ";
    }
    cout<<endl;*/
    
    r = attending.size();
    
    return r;
}

//--------------------------------------------
#define READ_FROM_FILE 1
void readInput()
{
    istream *pIstream = nullptr;
    
#if READ_FROM_FILE
    ifstream ifs;
    ifs.open("/Users/po/workGit/hackerRanck/sources/attendingWorkshops/testCases/sample7.txt", ios::in);
    //ifs.open("/Users/po/workGit/hackerRanck/sources/array-pairs/testCases/input01.txt", ios::in);
    //ifs.open("/Users/po/workGit/hackerRanck/sources/array-pairs/testCases/input04.txt", ios::in);
    //ifs.open("/Users/po/workGit/hackerRanck/sources/array-pairs/testCases/input05.txt", ios::in);
    
    pIstream = &ifs;
    
#else
    pIstream = &cin;
#endif
    
    //create root Node
    int n; // number of workshops
    *pIstream >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];
    
    for(int i=0; i < n; i++){
        *pIstream >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        *pIstream >> duration[i];
    }
    
    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    
}

int main(int argc, char *argv[]) {

    realisim::utils::Timer t;
    readInput();
    printf("elapse %f\n", t.getElapsed());
    
    return 0;
}
