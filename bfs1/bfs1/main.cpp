#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Node
{
private:
    int id;
    int shape;     //-1矩形 0三角 1圆
    int distance;
    Node * prevNode;
    vector<Node *> adjNodes;

public:
    Node(int key) :id(key), shape(1), distance(99999999), prevNode(NULL) {}
    int getId() { return id; }

    int getShape() { return shape; }
    void setShape(int s) { shape = s; }

    int getDistance() { return distance; }
    void setDistance(int d) { distance = d; }

    Node* getPrevNode() { return prevNode; }
    void setPrevNode(Node* n) { prevNode = n; }

    vector<Node *> getAdjNodes() { return adjNodes; }
    void pushAdjNode(Node* n) { adjNodes.push_back(n); }
};

void printPath(Node * node1, Node* node2)
{
    if (node1 == node2)
        cout << node1->getId();
    else
    {
        if (node2->getPrevNode() == NULL)
            cout << "no path from " << node1->getId() << " to " << node2->getId() << " exists" << endl;
        else
        {
            printPath(node1, node2->getPrevNode());
            cout << "->" << node2->getId() << "(" << node2->getDistance() << ")";
        }

    }
}

void BFS(vector<Node *> nodeList)
{
        Node* startNode = nodeList[0];
        for (Node* node : nodeList)
        {
            node->setDistance(INT_MAX);
            node->setPrevNode(NULL);
        }
        startNode->setDistance(0);
        startNode->setPrevNode(NULL);
        queue<Node*> visitQueue;
        visitQueue.push(startNode);
        while (!visitQueue.empty())
        {
            Node* current = visitQueue.front();
            visitQueue.pop();
            for (Node* adjNode : current->getAdjNodes())
            {
                if (adjNode->getDistance() == INT_MAX)
                {
                    adjNode->setDistance(current->getDistance() + 1);
                    adjNode->setPrevNode(current);
                    visitQueue.push(adjNode);
                }
            }
        }
}

int main()
{
    vector<Node *> nodeList;
    for (int i = 0; i < 10; i++)
    {
        Node * z = new Node(i);
        nodeList.push_back(z);
    }

    nodeList[0]->pushAdjNode(nodeList[1]);
    nodeList[0]->pushAdjNode(nodeList[2]);
    nodeList[0]->pushAdjNode(nodeList[3]);
    nodeList[1]->pushAdjNode(nodeList[4]);
    nodeList[1]->pushAdjNode(nodeList[5]);
    nodeList[2]->pushAdjNode(nodeList[1]);
    nodeList[2]->pushAdjNode(nodeList[5]);
    nodeList[3]->pushAdjNode(nodeList[5]);
    nodeList[3]->pushAdjNode(nodeList[6]);
    nodeList[4]->pushAdjNode(nodeList[7]);
    nodeList[5]->pushAdjNode(nodeList[4]);
    nodeList[5]->pushAdjNode(nodeList[8]);
    nodeList[6]->pushAdjNode(nodeList[8]);
    nodeList[6]->pushAdjNode(nodeList[9]);
    nodeList[7]->pushAdjNode(nodeList[8]);
    nodeList[8]->pushAdjNode(nodeList[4]);
    nodeList[9]->pushAdjNode(nodeList[8]);

    BFS(nodeList);
    for (int i = 1; i < nodeList.size(); i++)
    {
        printPath(nodeList[0], nodeList[i]);
        cout << endl;
    }
    system("pause");
    return 0;
}
