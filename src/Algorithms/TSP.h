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
//      struct leveled_node{
//         Node* node_;
//         int level_;
//         double weight_;
//         leveled_node(Node* node, int level, double weight){
//            node_ = node;
//            level_ = level;
//            weight_ = weight;
//         }
//         leveled_node(){
//            node_ = nullptr;
//            level_ = 0;
//            weight_ = 0;
//         }
//      };
      void BruteForceRecursion(int* start_id, Node* curr, double sum, double* l_bound, std::vector<Node*>* tour, std::vector<Node*>* best_tour,  Graph* g);
      
      Graph *NearestNeighbour(Graph *g);
      
      Graph *BranchNBound(Graph *g);
      
      Graph *DoubleTree(Graph *g);
      
};


#endif //MMI_TSP_H
