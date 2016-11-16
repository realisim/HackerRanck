#include <cmath>
#include <cstdio>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int kDistance = 6;

struct Node
{
  Node() : mId(-1), mVisited(false), mDistanceToReach(-1) {}
  ~Node() {}
  
  int mId;
  bool mVisited;
  int mDistanceToReach;
  
  vector<Node*> mChilds;
};

void clear(vector<Node*> iGraph)
{
  for(size_t i = 0; i < iGraph.size(); ++i)
  {
    delete iGraph[i];
  }
}

void makeQuery(Node* iStart)
{
  deque<Node*> queue;
  
  iStart->mDistanceToReach = 0;
  queue.push_back(iStart);
  while(!queue.empty())
  {
    Node* n = queue.front();
    
    if(!n->mVisited)
    {
      for(size_t i = 0; i < n->mChilds.size(); ++i)
      {
        Node* c = n->mChilds[i];
        queue.push_back(c);
        
        if( c->mDistanceToReach < 0)
        { c->mDistanceToReach = n->mDistanceToReach + kDistance; }
        else if( (n->mDistanceToReach + kDistance) < c->mDistanceToReach )
        {
          c->mDistanceToReach = n->mDistanceToReach + kDistance;
        }
      }
    }
    
    n->mVisited = true;
    queue.pop_front();
  }
}

void printResult(Node* iStart, const vector<Node*>& graph)
{
  for(size_t i = 0; i < graph.size(); ++i)
  {
    if( iStart != graph[i] )
    {
      cout << graph[i]->mDistanceToReach << " ";
    }
  }
  cout << endl;
}

int main() {

  int numQueries;
  
  cin >> numQueries;
  for(int i = 0; i < numQueries; ++i)
  {
    int numNodes;
    int numEdges;
    cin >> numNodes;
    cin >> numEdges;
    
    vector<Node*> graph;
    for(int j = 0; j < numNodes; ++j)
    {
      Node* n = new Node();
      n->mId = j+1;
      graph.push_back(n);
    }
    
    for(int j = 0; j < numEdges; ++j)
    {
      int nodeId0, nodeId1;
      cin >> nodeId0;
      cin >> nodeId1;
      
      Node* n0 = graph[nodeId0 - 1];
      Node* n1 = graph[nodeId1 - 1];
      
      n0->mChilds.push_back(n1);
      n1->mChilds.push_back(n0);
    }
    
    int query;
    cin >> query;

    //make the query
    makeQuery(graph[query-1]);
    printResult(graph[query-1], graph);
    clear(graph);
  }
  
  
  
  return 0;
}