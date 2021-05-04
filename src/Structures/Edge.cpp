//
// Created by mhenn on 4/28/2021.
//

#include "Edge.h"

Edge::Edge(Node *from, Node* to){
   from_ = from;
   to_ = to;
   
}

Edge::Edge(Node *from, Node *to, double weight){
   from_ = from;
   to_ = to;
   weight_ = weight;
}

Edge::Edge(int from, int to){
    Node f = Node(from);
    Node t = Node(to);
    from_ = &f;
    to_ = &t;
}

Edge::Edge(int from, int to, double weight){
   Node f = Node(from);
   Node t = Node(to);
   from_ = &f;
   to_ = &t;
   weight_ = weight;
}
