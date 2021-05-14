//
// Created by mhenn on 4/28/2021.
//

#ifndef MMI_NODE_H
#define MMI_NODE_H
//#include "Edge.h"
#include <vector>
class Edge;


class Node {
    public:
        Node* parent_ = this;
        int rank_ = 0;
        int id_ = 0;
        double dist_ = INFINITY;
        bool marked_ = false;
        std::vector<Edge*> edges_;
    public:
    Node(int id);
    void AddEdge(Edge* edge);
};

#endif //MMI_NODE_H
