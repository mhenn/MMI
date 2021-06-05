//
// Created by mhenn on 6/4/2021.
//

#include "CostFlow.h"

Graph* CostFlow::CreateResidual(Graph *g, std::vector<std::vector<double>>* F){
   
   auto* residual = new Graph(g->nodes_.size());
   
   for(auto n : g->nodes_)
      residual->nodes_[n->id_]->_balance = n->_balance;
   
   Node *from, *to;
   int f_id,t_id;
   double weight, capacity, flow, remainder;
   
   
   for(auto e : g->edges_){
      from = e->from_;
      to = e->to_;
      f_id = from->id_;
      t_id = to->id_;
      weight = e->weight_;
      capacity = e->capacity_;
      flow = F->at(f_id)[t_id];
      remainder = capacity - flow;
      if(f_id == 36 && t_id == 65)
         int i = 1;
      if (remainder == 0 ) {
         residual->AddEdge(t_id, f_id, weight * -1, flow, true);
         continue;
      }else if (flow == 0 ){
         residual->AddEdge(f_id, t_id, weight, capacity);
         continue;
      }
   
      residual->AddEdge(f_id, t_id, weight, capacity);
      residual->AddEdge(t_id,f_id, weight *-1, flow, true);
   }
   return residual;
}

std::vector<Edge*>* CostFlow::GetNegativeCycle(Graph r){
   
   auto* cycle = new std::vector<Edge*>();
   Node* tmp, *origin;
   Edge* e;
   int s = r.AddNode(0);
   
   for(auto n : r.nodes_)
      r.AddEdge(s,n->id_, 0,0);
   
   //e = SP::BellmanFord(&r, r.nodes_[s]);
   e = SP::BellmanFord(&r, r.nodes_[s]);
   
   if (!e)
      return cycle;
  
   tmp = e->to_;
   
   for(int i = 0; i < r.Size(); i++)
      tmp = tmp->parent_;
   
   origin = tmp;
   
   do{
      auto iter = std::find_if(tmp->parent_->edges_.begin(), tmp->parent_->edges_.end(), [&](Edge* e){ return e->to_->id_ == tmp->id_;});
      assert(iter != tmp->parent_->edges_.end());
      cycle->push_back(*iter);
      tmp = tmp->parent_;
   }while(tmp != origin);
   
   return cycle;
}

void CostFlow::cycle_canceling(Graph* g){

   int size = g->Size();
   double gamma = 0;
   std::vector<Edge*> *cycle;
   std::tuple<std::vector<Edge*>*, Edge*> neg_res;
   Graph* residual = g;
   Edge *edge = nullptr;
   std::vector<std::vector<double>> F(size+2, std::vector<double>(size + 2, 0));
   //Step 1: Get b_flow
   bool b_flow_exists = compute_b_flow(*g, &F);
   
   if(!b_flow_exists)
      return;
   
   while(true){
      //Step 2: Define Residual Graph
      residual = CostFlow::CreateResidual(g, &F);
   
      //Step 3: F augmenting cycle
      cycle = CostFlow::GetNegativeCycle(*residual);
      if( cycle->empty())
         break;
      
      double min ,remainder, cost, flow;
      int f, t;
      min = INFINITY;
      cost = 0;
      
      for(auto e : *cycle){
         f = e->from_->id_;
         t = e->to_->id_;
         flow = F[f][t];
         remainder = e->capacity_ - flow;
         if(e->residual)
            remainder = flow * -1;
         cost += e->weight_;
         std::cout << "|" << f << "->" << t << " " << F[f][t] << " cap" << e->capacity_ << " cost : " << e->weight_ << "|" << std::endl;
         
         if (remainder < min )
            min = remainder;
      }
      Edge* tmp = nullptr;
      //Step 4: update flow
      for(auto e : *cycle){
         f = e->from_->id_;
         t = e->to_->id_;
         if(e->residual)
            F[f][t] -= min;
         F[f][t] += min;
      }
      //Step 5: Repeat
   }
   double cost;
   int f, t;
   cost = 0;
   for(auto e: g->edges_){
      f = e->from_->id_;
      t = e->to_->id_;
      cost += (F[f][t] * e->weight_);
   }
   std::cout << cost << std::endl;
   
}


bool CostFlow::compute_b_flow(Graph g,  std::vector<std::vector<double>>* flow){
   
   //compute flow for super source/target
   std::vector<Node * > src_trgt = std::vector<Node*>();
   double b = 0.0;
   double src_flow = 0;
   double target_flow = 0;
   
   for(auto node : g.nodes_){
      b = node->_balance;
       if(b == 0)
          continue;
       
       if (b > 0)
          src_flow += b;
       else
          target_flow += b;
      src_trgt.emplace_back(node);
   }
   
   int src_node = g.AddNode(src_flow);
   int target_node = g.AddNode(target_flow);
   Edge* e = nullptr;
   double weight = 0;
   
   for(auto node : src_trgt){
      
      b = node->_balance;
      if (b > 0 )
         g.AddEdge(src_node, node->id_, 0, b);
      else
         g.AddEdge(node->id_, target_node, 0, b * -1);
   }
   
   
   double max_flow = Flow::EdmondsKarp(&g, g.nodes_[src_node], g.nodes_[target_node], flow);
   return max_flow == src_flow;
   
   
   
   //create those vertices
   //add edges to them
   
   
   

}