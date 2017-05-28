#include "P4_graph.h"

#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

Graph::Graph()
{
    _anzKnoten = 0;
    _nodes.clear();
}

Graph::~Graph()
{
    for (int i = 0; i < _nodes.size(); i++) {
        delete _nodes[i];
    }
    _nodes.clear();
}

//Get the node pointer by given key
GraphNode* Graph::GetNodeByKey(int key)
{
    for(int i = 0; i < _anzKnoten; i++)
    {
        GraphNode* currentNode = _nodes[i];
        if(currentNode->_key == key)
        {
            return currentNode;
        }
    }
    return nullptr;
}

//iterate all nodes and set _visited to false
void Graph::setAllUnvisited()
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        currentNode->_visited = false;
    }
}

//Check if all nodes are set to visited
bool Graph::checkVisited()
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        if(currentNode->_visited == false)
            return false;
    }
    return true;
}

bool Graph::init(std::string path)
{
    {
    std::ifstream file;
    file.open(path, std::ios_base::in);

    if (!file)
    {
        std::cout << "Cannot open file." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Start reading" << std::endl;

        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);

        std::cout << "Insert _anzKnoten" << std::endl;
        iss >> _anzKnoten;

        std::cout << "Create all Nodes" << std::endl;
        //Alle Knoten anlegen
        for(int i = 0; i < _anzKnoten; i++)
        {
            GraphNode* currentNode = new GraphNode(i);
            _nodes.push_back(currentNode);
        }

        std::cout << "Start creating edges" << std::endl;
        while (std::getline(file, line))
        {
            std::istringstream edges(line);
            int from, value, to;
            if (!(edges >> from >> to >> value)) { break; } // error

            std::cout << "From: " << from << " To: " << to << " Value: " << value << std::endl;
            GraphNode* currentNode = GetNodeByKey(from);
            GraphNode* currentNeighbour = GetNodeByKey(to);
            //Hinrichrung:
            GraphNode::edge edge(currentNeighbour, value);
            currentNode->_edges.push_back(edge);
            //Rückrichtung:
            GraphNode::edge backEdge(currentNode, value);
            currentNeighbour->_edges.push_back(backEdge);
        }
       return true;
    }

    return false;
}

}

bool Graph::print()
{
    if(_nodes.empty()) return false;
    //Print with Node ID: 1st neighbour, 2nd neighbour ...
    for(int i = 0; i < _anzKnoten; i++)
    {
        GraphNode* currentNode = _nodes[i];
        std::cout << currentNode->_key << " ";
        for(int k = 0; k < currentNode->_edges.size(); k++)
        {
            if(!currentNode->_edges.empty()){
                GraphNode::edge currentEdge = currentNode->_edges[k];
                std::cout << " -> " << currentEdge.node->_key << " [" << currentEdge.value << "] ";
            }
        }
        std::cout << std::endl;

    }

    return true;
}

//Implement here the depth-/breadfirstthsearch and Prim & Kruskal

//Implement this:
bool Graph::depthSearchRek(int startKey)
{
    return true;
}

bool Graph::breadthSearchIter(int startKey)
{
    return true;
}
//Or this
bool Graph::depthSearchIter(int startKey)
{
    std::stack<GraphNode*> st;

    st.push(_nodes[startKey]);

    //reset all nodes visit status
    for(auto& n : _nodes)
        n->_visited = false;

    while(!st.empty())
    {
        //obtain our top node and remove
        auto n = st.top();
        st.pop();

        //mark currently processed node as visited
        n->_visited = true;

        //add all edges to the stack
        for(auto e : n->_edges)
        {
            //only add to stack if not yet visited
            if(!e.node->_visited)
                st.push(e.node);
        }
    }

    //check our depth search
    for(auto n : _nodes)
        if(!n->_visited)
            return false;

    return true;
}

void Graph::breadthSearchHelper(GraphNode* x)
{
    x->_visited = true;

    for(auto e : x->_edges)
    {
        if(!e.node->_visited)
            breadthSearchHelper(e.node);
    }
}

bool Graph::breadthSearchRek(int startKey)
{
    //reset all nodes
    for(auto n : _nodes)
        n->_visited = false;

    breadthSearchHelper(_nodes[startKey]);

    //check our breadth search
    for(auto n : _nodes)
        if(!n->_visited)
            return false;

    return true;
}

//This must be done by you
double Graph::prim(int startKey)
{
    std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, std::greater<GraphNode::edge>> q;

    for(auto n : _nodes)
    {
        n->_prev = nullptr;
        n->_visited = false;
        n->_distance = std::numeric_limits<double>::max();
    }

    //add our current edges to the priorityqueue
    for(auto e : _nodes[startKey]->_edges)
    {
        q.push(e);
    }

    //start at our start node with a distance of 0
    auto curr = _nodes[startKey];
    curr->_distance = 0.0;
    curr->_visited = true;

    //go through every edge in the queue
    while(!q.empty())
    {
        //get our edge with the smallest weight
        auto e = q.top();
        q.pop();

        //if this fails we've already been here, skip to next edge/node
        if(!e.node->_visited)
        {
            //set the distance to this node
            e.node->_visited = true;
            e.node->_distance = e.value;
            e.node->_prev = curr;
            curr = e.node;

            //add all this nodes edge to the queue for traversal
            for(auto e : curr->_edges)
            {
                q.push(e);
            }
        }
    }

    //get the spanning tree size
    double res = 0.0;

    for(auto n : _nodes)
    {
        res += n->_distance;
    }

    return res;
}

int Graph::getId(GraphNode* n) const
{
    for(int i = 0; i < _nodes.size(); ++i)
    {
        if(_nodes[i] == n)
            return i;
    }

    return -1;
}

double Graph::kruskal()
{
    std::vector<std::pair<int, GraphNode::edge>> edges;
    std::vector<GraphNode::edge> mstEdges;

    //first: parent, second: rank
    std::vector<std::pair<int, int>> subSet(_nodes.size()+1);

    //define our function to find what set we're part of
    std::function<int(int)> findSet = [&](int key) -> int
    {
        if(subSet[key].first != key)
            subSet[key].first = findSet(subSet[key].first);

        return subSet[key].first;
    };

    auto merge = [&](int x, int y)
    {
        x = findSet(x);
        y = findSet(y);

        if(subSet[x].second > subSet[y].second)
        {
            subSet[y].first = x;
        }
        else // <=
            subSet[x].first = y;
        if(subSet[x].second == subSet[y].second)
            ++(subSet[y].second);

    };

    //just add all the edges
    for(int i = 0; i < _nodes.size(); ++i)
    {
        GraphNode* n = _nodes[i];

        //set all nodes to different set and parent of itself
        subSet[i].first = i;
        subSet[i].second = 0;

        n->_visited = false;
        for(auto e : n->_edges)
        {
            bool duplicate = false;
            //avoid duplicates
            for(auto pair : edges)
            {
                auto source = pair.first;
                auto edge = pair.second;

                //if it's already in the list don't add it
                if(e.node == _nodes[source] && edge.node == n)
                {
                    duplicate = true;
                    break;
                }


            }
            if(!duplicate)
                edges.push_back(std::pair<int, GraphNode::edge>(i, e));

        }
    }
    //that duplicate prevention actually works, nice

    //sort them from small to large, yes this works all good :)
    std::sort(edges.begin(), edges.end(), [](auto& lhs, auto& rhs) -> bool
    {
        return lhs.second.value < rhs.second.value;
    });

    //mst weight
    double res = 0.0;

    for(int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i].first;
        int v = getId(edges[i].second.node);

        if(v == -1)
            std::cerr << "something when wrong, couldn't find node key" << std::endl;

        int setu = findSet(u);
        int setv = findSet(v);

        //cycle is created if u and v belong to the same set
        if(setu != setv)
        {
            //std::cout << u << " - " << v << std::endl;
            res += edges[i].second.value;

            //join the sets together
            merge(u, v);
        }
    }

    return res;
}
