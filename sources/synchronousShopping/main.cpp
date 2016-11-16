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

struct FishBasket{
  explicit FishBasket(int iNumberOfFishType) : mNumberOfFishType(iNumberOfFishType)
  {
    mFishTypes = new bool[mNumberOfFishType];
    clear();
  }
  
  void add(int iType){
    //cout<<"add "<<iType<<endl;
    if(iType >=0 && iType <= mNumberOfFishType){
      mFishTypes[iType-1] = true;
    }
  }
  
  void add(const vector<int>& iTypes){
    for(int i = 0; i < iTypes.size(); ++i){
      add(iTypes[i]);
    }
  }
  
  void clear(){
    for(int i = 0; i < mNumberOfFishType; ++i){
      mFishTypes[i] = false;
    }
  }
  
  bool hasAllFishTypes(){
    bool r = true;
    for(int i = 0; i < mNumberOfFishType; ++i){
      r = r & mFishTypes[i];
    }
    return r;
  }
  
  int mNumberOfFishType;
  bool *mFishTypes;
};

map< pair<int, int>, int > gRoadWalkTime;

struct Node{
  Node() : mId(-1), mFishTypes(), mChilds() {}
  
  int mId;
  vector<int> mFishTypes;
  vector<Node*> mChilds;
};


void print(const vector<Node*>& iNodes){
  for(size_t i = 0; i < iNodes.size(); ++i){
    stringstream iss;
    const Node* n = iNodes[i];
    iss << n->mId;
    
    iss << " fish type: ";
    for(size_t j = 0; j < n->mFishTypes.size(); ++j){
      iss << n->mFishTypes[j] << ", ";
    }
    
    iss << " child nodes: ";
    for(size_t k = 0; k < n->mChilds.size(); ++k){
      iss << n->mChilds[k]->mId;
    }
    cout<<iss.str()<<endl;
  }
}

void print(string iString, const vector<Node*>& iPath)
{
  for(int j = 0; j < iPath.size(); ++j){
    cout << iPath.at(j)->mId << " ";
  }
  cout<<endl;
}

void print(string iName, int iFrom, int iTo, const vector< vector<Node*> >& iPaths)
{
  cout<<iName<<"from "<<iFrom<<" to "<<iTo<<endl;
  for(int i = 0; i < iPaths.size(); ++i){
    print("", iPaths.at(i));
  }
  
}

Node* findQuickestUnvisitedChilds(Node* iNode, const vector<Node*>& iVisited)
{
  Node* r = nullptr;
  
  vector<Node*> childs = iNode->mChilds;
  bool found = false;
  while( !found && !childs.empty() )
  {
    int quickest = numeric_limits<int>::max();
    auto it = childs.begin();
    auto itToQuickest = it;
    for(; it != childs.end(); ++it )
    {
      const int walkTime = gRoadWalkTime[ make_pair(iNode->mId, (*it)->mId) ];
      if( walkTime < quickest )
      {
        quickest = walkTime;
        itToQuickest = it;
      }
    }
    
    //is r already visited
    if( find( iVisited.begin(), iVisited.end(), *itToQuickest ) != iVisited.end() )
    {
      childs.erase(itToQuickest);
      r = nullptr;
    }
    else
    {
      r = *itToQuickest;
      found = true;
    }
  }
  
  return r;
}


void shortestPath(Node* iNode, Node* iEnd, vector<Node*>* iResult, vector<Node*>* iVisited)
{
  iResult->push_back(iNode);
  iVisited->push_back(iNode);
  
  if(iNode != iEnd)
  {
    //find quickest path to unvisited child
    Node* n = findQuickestUnvisitedChilds(iNode, *iVisited);
    if(n != nullptr)
    { shortestPath(n, iEnd, iResult, iVisited); }
  }
}

vector<Node*> shortestPath(Node* iStart, Node* iEnd)
{
  vector<Node*> r;
  vector<Node*> visited;
  
  shortestPath(iStart, iEnd, &r, &visited);
  
  return r;
}

int pathLength(const vector<Node*>& iV){
  int r = 0;
  
  for(int i = 0; i < iV.size() - 1; ++i){
    r += gRoadWalkTime[ make_pair(iV[i]->mId, iV[i+1]->mId) ];
  }
  
  //cout << "path length" << r << endl;
  return r;
}

int process(const vector<Node*>& iNodes, FishBasket& iFishBasket){
  //run 2 depth first from 2 different start node.
  //
  //if run0 finishes on node1 and run1 finishes on node0
  //it means that they can both finish at the same node.
  //From there, we have to make sure, they collected all
  //available fishes.
  //If so, those 2 path qualifies for a shortest path
  //where all fishes were bought.
  
  int smallestPath = numeric_limits<int>::max();
  for(size_t i = 1; i < iNodes.size(); ++i)
  {
    //big cat path
    vector<Node*> bcp = shortestPath(iNodes[0], iNodes[i]);
    //little cat path
    vector<Node*> lcp = shortestPath(iNodes[i], iNodes[0]);
    
    iFishBasket.clear();
        
    //add big cat fish to basket
    for(int k = 0; k < bcp.size(); ++k){
      //cout<<"big cat visits node" << bcp[k] << " and buys: ";
      iFishBasket.add(bcp[k]->mFishTypes);
    }
    
    //add little cat fish
    for(int k = 0; k < lcp.size(); ++k){
      iFishBasket.add(lcp[k]->mFishTypes);
    }
    
    if(iFishBasket.hasAllFishTypes())
    {
      //make sure both cat ends at node n.
//          const int lastNodeId = iNodes[iNodes.size()-1]->mId;
//          if( bcp[bcp.size()-1]->mId != lastNodeId )
//          {
//            bcp = extendPathTo(bcp, lastNodeId);
//          }
//          
//          if( lcp[lcp.size()-1]->mId != lastNodeId )
//          {
//            lcp = extendPathTo(bcp, lastNodeId);
//          }
      
      smallestPath = min(smallestPath,
                         max(pathLength(bcp), pathLength(lcp) ) );
      
      
      
      print("big cat path: ", bcp);
      print("little cat path: ", lcp);
      cout <<"all fish bought. path lenght is: "<< max(pathLength(bcp), pathLength(lcp) )<<
      " smallest path is: "<<smallestPath;
    }
    
    
    cout<<endl<<endl;

  }
  return smallestPath;
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int n, m, k;
  cin >> n >> m >> k;
  
  //cout<<n<<m<<k<<endl;
  FishBasket fishBasket(k);
  
  vector<Node*> mNodes;
  for(int i = 0; i < n; ++i){
    Node* n = new Node();
    n->mId = i+1;
    mNodes.push_back(n);
  }
  
  //insert fist sold by fishmonger.
  for(int i = 0; i < n; ++i)
  {
    int numFishType = 0;
    cin >> numFishType;
    Node* n = mNodes[i];
    for(int j = 0; j < numFishType; ++j){
      int fishType;
      cin >> fishType;
      n->mFishTypes.push_back(fishType);
    }
  }
  
  //insert the road and time;
  for(int i = 0; i < m; ++i){
    int fromId, toId, walkTime;
    cin >> fromId >> toId >> walkTime;
    
    Node* n = mNodes[fromId-1];
    n->mChilds.push_back( mNodes[toId-1] );
    gRoadWalkTime.insert( make_pair( make_pair(fromId, toId), walkTime ) );
    
    n = mNodes[toId-1];
    n->mChilds.push_back( mNodes[fromId-1] );
    gRoadWalkTime.insert( make_pair( make_pair(toId, fromId), walkTime ) );
  }
  
  print(mNodes);
  
  cout << process(mNodes, fishBasket);
  return 0;
}
