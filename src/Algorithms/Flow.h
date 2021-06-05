//
// Created by mhenn on 5/29/2021.
//

#ifndef MMI_FLOW_H
#define MMI_FLOW_H
#include "SP.h"

class Flow {
      
   public:
      
      static double EdmondsKarp(Graph *g, Node *s, Node *t, std::vector<std::vector<double>>* flow);
      
      static bool
      FlowBSF(Graph *g, std::vector<std::vector<double>> capacity, std::vector<std::vector<double>> flow, Node *start,
              Node *dst);
};


#endif //MMI_FLOW_H
