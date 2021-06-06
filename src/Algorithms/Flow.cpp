//
// Created by mhenn on 5/29/2021.
//

#include "Flow.h"
/*


double Flow::EdmondsKarp(Graph *g, Node *s, Node *t) {
   
   g->ClearEdges();
   Node* tmp = nullptr;
   Edge* inverse;
   double min = INFINITY;
   g = SP::BellmanFord(g, s);
   double flow = 0.0;
   
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
      if (min < INFINITY)
         flow+= min;
   }
   
   return flow;
}
*/

double Flow::EdmondsKarp(Graph *g, Node *s, Node *t, std::vector<std::vector<double>>* flow) {
   double max_flow = 0.0;
   int size = g->nodes_.size();
   std::vector<std::vector<double>> capacity = g->GetCapacityMatrix();
   Node* tmp = t;
   double  min = INFINITY;
   double remainder = 0.0;
   int u, v;
   g->Clear();
   bool path_exists = FlowBSF(g,capacity,*flow,s,t);
   
   while(path_exists){
      while(tmp->parent_ != tmp){
         u = tmp->parent_->id_;
         v = tmp->id_;
         remainder = capacity[u][v] - flow->at(u)[v];
         if(min > remainder)
            min = remainder;
         tmp = tmp->parent_;
      }
      tmp = t;
      while(tmp->parent_ != tmp and min != INFINITY){
         u = tmp->parent_->id_;
         v = tmp->id_;
         flow->at(u)[v] += min;
         flow->at(v)[u] -= min;
         tmp = tmp->parent_;
      }
      min = INFINITY;
      g->Clear();
      path_exists = FlowBSF(g,capacity,*flow,s,t);
   }
   
   for(int i =0; i < size; i++)
      max_flow += flow->at(i)[t->id_];
   return max_flow;
}


bool Flow::FlowBSF(Graph*g,std::vector<std::vector<double>> capacity, std::vector<std::vector<double>> flow, Node* start, Node* dst){
      g->Clear();
      start->marked_ = true;
      std::queue<Node*> queue = std::queue<Node*>();
      queue.push(start);
      Node* u, *v;
      while(!queue.empty()){
         u = queue.front();
         int u_id = u->id_;
         queue.pop();
         for(int i = 0; i < g->nodes_.size(); i++){
            v = g->nodes_.at(i);
            if(capacity[u_id][i] - flow[u_id][i] > 0 and !v->marked_) {
               v->marked_ = true;
               queue.push(v);
               v->parent_ = u;
               if (v == dst)
                  return true;
            }
         }
      }
      return false;
}


