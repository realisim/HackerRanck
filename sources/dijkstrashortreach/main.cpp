#include <cmath>
#include <cstdio>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <sstream>
using namespace std;

struct Node
{
  Node() : mId(-1), mVisited(false), mDistanceToReach(std::numeric_limits<int>::max()) {}
  ~Node() {}
  
  int mId;
  bool mVisited;
  int mDistanceToReach;
  
  vector<Node*> mChilds;
  vector<int> mDistanceToChild;
};

void clear(vector<Node*> iGraph)
{
  for(size_t i = 0; i < iGraph.size(); ++i)
  {
    delete iGraph[i];
  }
}

typedef pair<int, int> DistanceToNodeIndex;
void makeQuery(vector<Node*>& iGraph, int iStartNode)
{
  iGraph[iStartNode-1]->mDistanceToReach = 0;

  priority_queue<DistanceToNodeIndex,
    std::vector<DistanceToNodeIndex>, std::greater<DistanceToNodeIndex> > pQueue;
  
  pQueue.push( make_pair(0, iStartNode) );

  Node *n = nullptr;
  while(!pQueue.empty())
  {
    n = iGraph[pQueue.top().second - 1];
    pQueue.pop();
    
    if( !n->mVisited )
    {
      for(size_t i = 0; i < n->mChilds.size(); ++i)
      {
        Node* c = n->mChilds[i];
        
        int d = n->mDistanceToChild[i];
        
        const int newD = n->mDistanceToReach + d;
        if( newD < c->mDistanceToReach )
        {
          c->mDistanceToReach = newD;
          pQueue.push( make_pair(newD, c->mId) );
        }
      }
    }
    
    n->mVisited = true;
  }
}

string printResult(Node* iStart, const vector<Node*>& graph)
{
  ostringstream iss;
  for(size_t i = 0; i < graph.size(); ++i)
  {
    if( iStart != graph[i] )
    {
      int d = graph[i]->mDistanceToReach;
      if( d == std::numeric_limits<int>::max() )
        d = -1;
      iss << d << " ";
    }
  }
  iss << endl;
  
  return iss.str();
}

void showAllEdgesPerNode(const vector<Node*>& graph)
{
  printf("\n\n all egdges per nodes:\n");
  for(size_t i = 0; i < graph.size(); ++i)
  {
    const Node* n = graph[i];
    printf("\tnode %d: \n", n->mId);
    for(size_t j = 0; j < n->mChilds.size(); ++j)
    {
      const Node* c = n->mChilds[j];
      printf("\t\tchild: %d dist: %d\n", c->mId, n->mDistanceToChild[j]);
    }
  }
}

void doWithFile()
{
  vector<string> results;
  
  int numQueries;
  FILE *pFile;
  pFile = fopen ("/Users/po/Desktop/input07.txt","r");
  
  //scanf("%d", &numQueries);
  fscanf(pFile, "%d", &numQueries);
  for(int i = 0; i < numQueries; ++i)
  {
    int numNodes;
    int numEdges;
    //scanf("%d", &numNodes);
    //scanf("%d", &numEdges);
    fscanf(pFile, "%d", &numNodes);
    fscanf(pFile, "%d", &numEdges);
    
    vector<Node*> graph;
    graph.reserve(numNodes);
    for(int j = 0; j < numNodes; ++j)
    {
      Node* n = new Node();
      n->mId = j+1;
      graph.push_back(n);
    }
    
    
    for(int j = 0; j < numEdges; ++j)
    {
      int nodeId0, nodeId1, distance;
      fscanf(pFile, "%d", &nodeId0);
      fscanf(pFile, "%d", &nodeId1);
      fscanf(pFile, "%d", &distance);
      
      Node* n0 = graph[nodeId0 - 1];
      Node* n1 = graph[nodeId1 - 1];
      
      n0->mChilds.push_back(n1);
      n0->mDistanceToChild.push_back(distance);
      n1->mChilds.push_back(n0);
      n1->mDistanceToChild.push_back(distance);
    }
    
    int query;
    fscanf(pFile, "%d", &query);
    
    //make the query
    makeQuery(graph, query);
    //showAllEdgesPerNode(graph);
    
    results.push_back( printResult(graph[query-1], graph) );
    clear(graph);
    graph.clear();
  }
  
  //print results
  for(size_t i = 0; i < results.size(); ++i)
  {
    cout << results[i];
  }
}

void doWithStdin()
{
  vector<string> results;
  
  int numQueries;
  
  scanf("%d", &numQueries);
  for(int i = 0; i < numQueries; ++i)
  {
    int numNodes;
    int numEdges;
    scanf("%d", &numNodes);
    scanf("%d", &numEdges);
    
    vector<Node*> graph;
    graph.reserve(numNodes);
    for(int j = 0; j < numNodes; ++j)
    {
      Node* n = new Node();
      n->mId = j+1;
      graph.push_back(n);
    }
    
    
    for(int j = 0; j < numEdges; ++j)
    {
      int nodeId0, nodeId1, distance;
      scanf("%d", &nodeId0);
      scanf("%d", &nodeId1);
      scanf("%d", &distance);
      
      Node* n0 = graph[nodeId0 - 1];
      Node* n1 = graph[nodeId1 - 1];
      
      n0->mChilds.push_back(n1);
      n0->mDistanceToChild.push_back(distance);
      n1->mChilds.push_back(n0);
      n1->mDistanceToChild.push_back(distance);
    }
    
    int query;
    scanf("%d", &query);
    
    //make the query
    makeQuery(graph, query);
    //showAllEdgesPerNode(graph);
    
    results.push_back( printResult(graph[query-1], graph) );
    clear(graph);
    graph.clear();
  }
  
  //print results
  for(size_t i = 0; i < results.size(); ++i)
  {
    cout << results[i];
  }
}


int main() {
  std::ios::sync_with_stdio(false);
  
  doWithStdin();
  //doWithFile();
  
  return 0;
}