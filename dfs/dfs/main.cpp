#include<iostream>
#include<vector>
#include<queue>

using namespace std;

enum Shape { CIRCLE, TRIANGLE, SQUARE };

class Node
{
private:
    int _id;

    int _d;
    int _f;

    Shape _shape;
    Node * _prevNode;
    vector<Node *> _adjNodeList;

    static int _countNodeId;
public:
    Node();

    int getId() { return _id; }

    void setShape(Shape shape) { _shape = shape; }
    Shape getShape() { return _shape; }

    void setD(int d) { _d = d; }
    int getD() { return _d; }

    void setF(int f) { _f = f; }
    int getF() { return _f; }

    void setPrevNode(Node * node) { _prevNode = node; }
    Node * getPrevNode() { return _prevNode; }

    void pushAdjNode(Node * node) { _adjNodeList.push_back(node); }
    vector<Node *> getAdjNodeList() { return _adjNodeList; }

    void print();
};

int Node::_countNodeId = 0;

Node::Node()
{
    _id = _countNodeId++;
    _d = -1;
    _f = -1;
    _shape = CIRCLE;
    _prevNode = NULL;
}

void Node::print()
{
    cout << "Node: id_" << _id << " shape_" << _shape << " d_" << _d << " f_" << _f
        << " adj";
    for (int i = 0; i < _adjNodeList.size(); i++)
    {
        cout << "_" << _adjNodeList[i]->getId();
    }
    cout << endl;
}

class Edge
{
private:
    int _id;
    Node * _startNode;
    Node * _endNode;

public:
    Edge(Node * startNode, Node * endNode);
};


Edge::Edge(Node * startNode, Node * endNode)
    :_startNode(startNode), _endNode(endNode)
{
    _startNode->pushAdjNode(_endNode);
}

class Graph
{
private:
    vector<Node *> _nodeList;

public:
    Graph(vector<Node *> nodes) :_nodeList(nodes) {};

    Node * getNode(int id) { return _nodeList[id]; }
    vector<Node *> getNodeList() { return _nodeList; }

    void print();
};

Graph * buildGraph()
{
    vector<Node *> nodes;
    for (int i = 0; i < 8; i++)
    {
        Node * node1 = new Node();
        nodes.push_back(node1);
    }

    Edge * edge0 = new Edge(nodes[0], nodes[7]);
    Edge * edge1 = new Edge(nodes[0], nodes[4]);
    Edge * edge2 = new Edge(nodes[1], nodes[3]);
    Edge * edge3 = new Edge(nodes[1], nodes[2]);
    Edge * edge4 = new Edge(nodes[2], nodes[3]);
    Edge * edge5 = new Edge(nodes[3], nodes[0]);
    Edge * edge6 = new Edge(nodes[3], nodes[4]);
    Edge * edge7 = new Edge(nodes[4], nodes[5]);
    Edge * edge8 = new Edge(nodes[5], nodes[7]);
    Edge * edge9 = new Edge(nodes[6], nodes[5]);
    Edge * edge10 = new Edge(nodes[7], nodes[4]);
    Edge * edge11 = new Edge(nodes[7], nodes[6]);

    Graph * newGraph = new Graph(nodes);
    return newGraph;
}

void Graph::print()
{
    for (int i = 0; i < _nodeList.size(); i++)
    {
        _nodeList[i]->print();
    }
}

void DFS_VISIT(Node * node, int &time)
{
    time++;
    node->setD(time);
    node->setShape(TRIANGLE);
    vector<Node*> adjList = node->getAdjNodeList();
    for (int i = 0; i < adjList.size(); i++)
    {
        Node* adjNode = adjList[i];
        if (adjNode->getShape() == CIRCLE)
        {
            adjNode->setPrevNode(node);
            DFS_VISIT(adjNode, time);
        }
    }
    node->setShape(SQUARE);
    time++;
    node->setF(time);
}

void DFS(Graph * graph, Node * startNode)
{
    int time = 0;
    for (int i = 0; i < graph->getNodeList().size(); i++)
    {
        graph->getNodeList()[i]->setShape(CIRCLE);
        graph->getNodeList()[i]->setPrevNode(NULL);
    }
    DFS_VISIT(startNode, time);
    for (int i = 0; i < graph->getNodeList().size(); i++)
    {
        Node* node = graph->getNodeList()[i];
        if (node->getShape() == CIRCLE)
        {
            DFS_VISIT(node, time);
        }
    }
}

int main()
{
    Graph * newGraph = buildGraph();
    cout << "Befroe DFS" << endl;
    newGraph->print();

    cout << endl << "After DFS" << endl;
    DFS(newGraph, newGraph->getNode(2));
    newGraph->print();

    system("pause");
}
