#ifndef GRAPH_H
#define GRAPH_H

#include "P4_graphnode.h"
#include <deque>
#include <map>
#include <queue>
#include <iostream>

class Graph
{
public:
    Graph();
    ~Graph();

    GraphNode* GetNodeByKey(int key);
    void setAllUnvisited();
    bool checkVisited();
    bool init(std::string path);
    bool print();

    //Implement this:
    bool depthSearchRek(int startKey);
    bool breadthSearchIter(int startKey);
    //Or this
    bool depthSearchIter(int startKey);
    void breadthSearchHelper(GraphNode* x);
    bool breadthSearchRek(int startKey);
    int getId(GraphNode* x) const;

    //This must be done by you
    double prim(int startKey);
    double kruskal();

    //They might be helpful
    int _anzKnoten;
    bool _ger, _gew;
    std::vector<GraphNode*> _nodes;
};

#endif // GRAPH_H
