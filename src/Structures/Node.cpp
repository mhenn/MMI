//
// Created by mhenn on 4/28/2021.
//
#include "Node.h"

Node::Node(int id){
   id_ = id;
   edges_ = std::vector<Edge*>();
}

void Node::AddEdge(Edge* edge){
   edges_.push_back(edge);
}
