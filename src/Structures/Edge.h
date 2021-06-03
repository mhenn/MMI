//
// Created by mhenn on 4/28/2021.
//

#ifndef MMI_EDGE_H
#define MMI_EDGE_H

#include "Node.h"
//class Node;

class Edge {
   public:
      Node *from_;
      Node *to_;
      double weight_ = 0;
      //double flow_ = 0;
      
      Edge(){}
      ~Edge(){}
      Edge(Node *from, Node* to);
      
      Edge(Node *from, Node *to, double weight);
      
      Edge(int from, int to);
      
      Edge(int from, int to, double weight);
      
      bool operator <(const Edge* e)const {
         return weight_ < e->weight_;
      }
      bool operator >(const Edge* e)const{
         return weight_ > e->weight_;
      }
      bool operator ()(const Edge* a,const Edge* e)const{
        return a < e;
      }
};


#endif //MMI_EDGE_H
