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

//
//https://www.hackerrank.com/challenges/swap-nodes-algo
//

struct Node
{
    Node() : mValue(1), mLeft(nullptr), mRight(nullptr) {}
    
    int mValue;
    Node* mLeft;
    Node* mRight;
};

Node root;
deque<int> nodeIndices;
vector<int> swapsToPerform;
//--------------------------------------------
#define READ_FROM_FILE 1
void readInput()
{
    istream *pIstream = nullptr;
    
#if READ_FROM_FILE
    ifstream ifs;
    ifs.open("/Users/po/workGit/hackerRanck/sources/swapNodeAlgo/testCases/sample.txt", ios::in);
    //ifs.open("/Users/po/workGit/hackerRanck/sources/array-pairs/testCases/input01.txt", ios::in);
    //ifs.open("/Users/po/workGit/hackerRanck/sources/array-pairs/testCases/input04.txt", ios::in);
    //ifs.open("/Users/po/workGit/hackerRanck/sources/array-pairs/testCases/input05.txt", ios::in);
    
    pIstream = &ifs;
    
#else
    pIstream = &cin;
#endif
    
    //create root Node

    int N, T;
    *pIstream >> N;
    nodeIndices.resize(N*2);

    for(int i = 0; i < N; ++i)
    {
        int a, b;
        *pIstream >> a;
        *pIstream >> b;
        nodeIndices[i*2 + 0] = a;
        nodeIndices[i*2 + 1] = b;
    }
    
    *pIstream >> T;
    swapsToPerform.resize(T);
    for(int i = 0; i < T; ++i)
    {
        int a;
        *pIstream >> a;
        swapsToPerform[i] = a;
    }
}

void createTree()
{
    // breadth first creation...
    deque<Node*> toVisit;
    toVisit.push_back(&root);
    
    while(!toVisit.empty())
    {
        Node *n = toVisit.front();
        toVisit.pop_front();
        
        if(!nodeIndices.empty())
        {
            int a = nodeIndices.front();
            nodeIndices.pop_front();
            
            int b = nodeIndices.front();
            nodeIndices.pop_front();
            
            Node *nl, *nr;
            
            if(a != -1)
            {
                nl = new Node(); nl->mValue = a;
                n->mLeft = nl;
                toVisit.push_back(nl);
            }
            
            if(b != -1)
            {
                nr = new Node(); nr->mValue = b;
                n->mRight = nr;
                toVisit.push_back(nr);
            }
            
        }
    }
}

void swap(Node* pNode, int currentDepth, int iSwapDepth)
{
    // swapping occurs at 1*iSwapDepth, 2*iSwapDepth, 3*iSwapDepth...
    if(pNode)
    {
        if(currentDepth >= iSwapDepth &&
           currentDepth % iSwapDepth  == 0)
        {
            Node* t = pNode->mLeft;
            pNode->mLeft = pNode->mRight;
            pNode->mRight = t;
        }
        
        ++currentDepth;
        swap(pNode->mLeft, currentDepth, iSwapDepth);
        swap(pNode->mRight, currentDepth, iSwapDepth);
    }
}

void print(Node* pNode)
{
    if(pNode)
    {
        print(pNode->mLeft);
        cout << pNode->mValue << " ";
        print(pNode->mRight);
    }
}

void printTree()
{
    print(&root);
    cout << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    readInput();
    
    createTree();
    //printTree();
    
    for(size_t i = 0; i < swapsToPerform.size(); ++i)
    {
        swap(&root, 1, swapsToPerform[i]);
        printTree();
    }
    
    return 0;
}
