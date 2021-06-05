//
// Created by mhenn on 6/4/2021.
//

#ifndef MMI_COSTFLOW_H
#define MMI_COSTFLOW_H
#include "Flow.h"
#include "TSP.h"
#include <cassert>

class CostFlow {
      
   
   public:
      static void cycle_canceling(Graph *g);
      
      static Graph *CreateResidual(Graph *g, std::vector<std::vector<double>> *F);
      
      //static bool compute_b_flow(Graph *g, std::vector<std::vector<double>> *flow);
      
      static std::vector<Edge *> *GetNegativeCycle(Graph r);
      
      static bool compute_b_flow(Graph g, std::vector<std::vector<double>> *flow);
};


#endif //MMI_COSTFLOW_H
