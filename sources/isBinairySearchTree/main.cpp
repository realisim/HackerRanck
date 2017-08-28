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
//https://www.hackerrank.com/challenges/is-binary-search-tree/problem
//

//--------------------------------------------
struct Node
{
    Node() : data(0), left(nullptr), right(nullptr) {}
    
    int data;
    Node* left;
    Node* right;
};

Node *gpRoot = nullptr;

void readInput()
{


    
    Node *n1 = new Node(); n1->data = 1;
    Node *n2 = new Node(); n2->data = 2;
    Node *n3 = new Node(); n3->data = 3;
    Node *n4 = new Node(); n4->data = 4;
    Node *n5 = new Node(); n5->data = 5;
    Node *n6 = new Node(); n6->data = 6;
    Node *n7 = new Node(); n7->data = 7;
    
    // bst
//    n4->left = n2;
//    n4->right = n6;
//    
//    n2->left = n1;
//    n2->right = n3;
//    
//    n6->left = n5;
//    n6->right = n7;
//    
//    gpRoot = n4;
    
    // non bst test case 1
//    n3->left = n2;
//    n3->right = n6;
//    
//    n2->left = n1;
//    n2->right = n4;
//    
//    n6->left = n5;
//    n6->right = n7;
//    
//    gpRoot = n3;
    
    // non bst test case 2
    n5->left = n2;
    n5->right = n6;
    
    n2->left = n1;
    n2->right = n3;
    
    n6->left = n4;
    n6->right = n7;
    
    gpRoot = n5;
}


enum side{sLeft, sRight};

void checkBst(Node *n, int &ioMin, int &ioMax, bool &ioIsBst, side iSide)
{
    if(!n) return;
    
    if(ioIsBst)
    {
        ioMin = min(ioMin, n->data);
        ioMax = max(ioMax, n->data);
        
        if(n->left){ ioIsBst &= n->left->data < n->data; }
        if(n->right){ ioIsBst &= n->right->data > n->data; }
        
        if(iSide == sLeft)
        {
            if(n->left){ ioIsBst &= n->left->data < ioMax; }
            if(n->right){ ioIsBst &= n->right->data < ioMax; }
        }
        else
        {
            if(n->left){ ioIsBst &= n->left->data > ioMin; }
            if(n->right){ ioIsBst &= n->right->data > ioMin; }
        }
        
        checkBst(n->left, ioMin, ioMax, ioIsBst, iSide);
        checkBst(n->right, ioMin, ioMax, ioIsBst, iSide);
    }
}


bool checkBST(Node* root) {
    
    bool isBst = true;
    int iMin = root->data;
    int iMax = root->data;
    checkBst(root->left, iMin, iMax, isBst, sLeft);
    
    iMin = root->data;
    iMax = root->data;
    checkBst(root->right, iMin, iMax, isBst, sRight);
    return isBst;
    //return true;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    readInput();
    
    printf("%s", checkBST(gpRoot) ? "yes" : "no");
    return checkBST(gpRoot);
    
}
