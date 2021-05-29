//
// Created by mhenn on 5/29/2021.
//

#include "Flow.h"


Graph* Flow::EdmondsKarp(Graph *g, Node *s, Node *t) {
   
   g->ClearEdges();
   Node* tmp = nullptr;
   Edge* inverse;
   double min = INFINITY;
   g = SP::BellmanFord(g, s);
   
   while(t->parent_ != t){
      g->Clear();
      g->BuildResidual();
      t->parent_ = t;
      g = SP::BellmanFord(g, s);
      min = INFINITY;
      for(int i = 0; i < 2;i++) {
         
         tmp = t;
         while (tmp->parent_ != tmp) {
            Edge* edge = g->GetEdge(tmp->parent_, tmp);
            if (i == 0){
               if (edge->CapacityRemainder() < min )
                  min = edge->CapacityRemainder();
            }
            else {
               edge->weight_ += min;
               if(edge->is_residual_){
                  inverse = g->GetEdge(edge->to_, edge->from_);
                  inverse->weight_ -= min;
               }
            }
            tmp = tmp->parent_;
         }
      }
   }
   return g;
}

bool Flow::PathExists(Node* start, Node* goal){
   Node* tmp = start;
   
   while (tmp->parent_ != tmp)
      tmp = tmp->parent_;
   return tmp == goal;
}

void Flow::PrintMaxFlow(Graph *g, Node *node) {
   double max_flow = 0.0;
   std::vector<Edge*>* edges = g->GetAllEdgesTo(node);
   for (auto e: *edges)
      max_flow += e->weight_;
   
   std::cout << max_flow << std::endl;

}
