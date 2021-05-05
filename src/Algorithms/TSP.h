//
// Created by mhenn on 4/30/2021.
//

#ifndef MMI_TSP_H
#define MMI_TSP_H

#include "../Structures/Graph.h"
#include <iostream>
#include <utility>
#include "MST.h"
#include "Search.h"

class TSP {
   public:
      
      static Graph *NearestNeighbour(Graph *g, bool print);
      
      static Graph *DoubleTree(Graph *g, bool print);
      
      //std::vector<Node*> BranchNBound(Graph *g, bool test_all);
      static Graph* BranchNBound(Graph *g, bool test_all);
      
      
      //void BruteForceRecursion(int *start_id, Node *curr, double sum, double *l_bound, std::vector<Node *> *tour,
      //                         std::vector<Node *> *best_tour, Graph *g, bool *test_all);
      
      static void BruteForceRecursion(int *start_id, Node *curr, double sum, double *l_bound, std::vector<Edge *> *tour,
                               std::vector<Edge *> *best_tour, Graph *g, bool *test_all);
};


#endif //MMI_TSP_H
