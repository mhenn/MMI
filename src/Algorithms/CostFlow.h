//
// Created by mhenn on 6/4/2021.
//

#ifndef MMI_COSTFLOW_H
#define MMI_COSTFLOW_H
#include "Flow.h"
#include "TSP.h"

class CostFlow {
      
      static bool compute_b_flow(Graph *g);
   
   public:
      static void cycle_canceling(Graph *g);
};


#endif //MMI_COSTFLOW_H