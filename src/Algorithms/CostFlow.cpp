//
// Created by mhenn on 6/4/2021.
//

#include "CostFlow.h"



void CostFlow::cycle_canceling(Graph* g){

   //Step 1: Get b_flow
   compute_b_flow(g);
   //Step 2: Define Residual Graph
   //Step 3:
   //Step 4
   //Step 5
   
   
}


bool CostFlow::compute_b_flow(Graph* g){
   
   //compute flow for super source/target
   std::vector<Node * > src_trgt = std::vector<Node*>();
   double b = 0.0;
   double src_flow = 0;
   double target_flow = 0;
   
   for(auto node : g->nodes_){
      b = node->_balance;
       if(b == 0)
          continue;
       
       if (b > 0)
          src_flow += b;
       else
          target_flow += b;
      src_trgt.emplace_back(node);
   }
   
   int src_node = g->AddNode(src_flow);
   int target_node = g->AddNode(target_flow);
   Edge* e = nullptr;
   double weight = 0;
   
   for(auto node : src_trgt){
      
      b = node->_balance;
      if (b > 0 )
         g->AddEdge(src_node, node->id_, 0, b);
      else
         g->AddEdge(node->id_, target_node, 0, b * -1);
   }
   
   double flow = Flow::EdmondsKarp(g, g->nodes_[src_node], g->nodes_[target_node]);
   return flow == src_flow;
   
   //create those vertices
   //add edges to them
   
   
   

}