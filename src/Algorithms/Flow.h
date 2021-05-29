//
// Created by mhenn on 5/29/2021.
//

#ifndef MMI_FLOW_H
#define MMI_FLOW_H
#include "SP.h"

class Flow {
   
   
   public:
      static Graph* EdmondsKarp(Graph* g, Node* s, Node* t);
      
      static void PrintMaxFlow(Graph *pGraph, Node *pNode);
      
      static bool PathExists(Node *start, Node *goal);
};


#endif //MMI_FLOW_H
