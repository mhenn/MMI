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
      //TODO Transparenz ,continue, letzter Punkt kann gespart werden
      if (remainder == 0 ) {
         residual->AddEdge(t_id, f_id, weight * -1, 0, true);
         continue;
      }else if (flow == 0 ){
         residual->AddEdge(f_id, t_id, weight, capacity);
         continue;
      }
   
      residual->AddEdge(f_id, t_id, weight, capacity);
      residual->AddEdge(t_id,f_id, weight *-1, 0, true);
   }
   return residual;
}

double MinFromPath(std::vector<Edge*>* path, std::vector<std::vector<double>>* F){
   
   double min ,remainder,  flow;
   int f, t;
   min = INFINITY;
   
   for(auto e : *path){
      f = e->from_->id_;
      t = e->to_->id_;
      flow = (*F)[f][t];
      remainder = e->capacity_ - flow;
      
      if (remainder < min )
         min = remainder;
   }
   
   return min;
}

void UpdateFlow(std::vector<Edge*>* path, std::vector<std::vector<double>>* F, double gamma){
   int t,f;
   for(auto e : *path){
      f = e->from_->id_;
      t = e->to_->id_;
      if(e->residual) {
         (*F)[t][f] -= gamma;
         (*F)[f][t] += gamma;
         continue;
      }
      
      (*F)[f][t] += gamma;
      (*F)[t][f] -= gamma;
   }
}

void PathFromPredecessor(Node* src, Node* target, std::vector<Edge*>* path){
 
   Node* tmp;
   tmp = src;
   
   do{
      auto iter = std::find_if(tmp->parent_->edges_.begin(), tmp->parent_->edges_.end(), [&](Edge* e){ return e->to_->id_ == tmp->id_;});
      assert(iter != tmp->parent_->edges_.end());
      path->push_back(*iter);
      tmp = tmp->parent_;
   }while(tmp != target);
}

double CalculateCost(std::vector<Edge*>* edges, std::vector<std::vector<double>>* F){
   double cost;
   int f, t;
   cost = 0;
   for(auto e: *edges){
      f = e->from_->id_;
      t = e->to_->id_;
      cost += ((*F)[f][t] * e->weight_);
   }
   return cost;
}

std::vector<Edge*>* CostFlow::GetNegativeCycle(Graph r){
   
   auto* cycle = new std::vector<Edge*>();
   Node* tmp, *origin;
   Edge* e;
   int s = r.AddNode(0);
   
   for(auto n : r.nodes_)
      r.AddEdge(s,n->id_, 0,0);
   
   e = SP::BellmanFord(&r, r.nodes_[s]);
   
   if (!e)
      return cycle;
  
   tmp = e->to_;
   
   for(int i = 0; i < r.Size(); i++)
      tmp = tmp->parent_;
   
   PathFromPredecessor(tmp,tmp,cycle);
   
   return cycle;
}

bool CostFlow::cycle_canceling(Graph* g){

   int size = g->Size();
   std::vector<Edge*> *cycle;
   Graph* residual;
   double min;
   std::vector<std::vector<double>> F(size+2, std::vector<double>(size + 2, 0));
   //Step 1: Get b_flow
   bool b_flow_exists = compute_b_flow(*g, &F);
   
   if(!b_flow_exists)
      return false;
   
   while(true){
      //Step 2: Define Residual Graph
      residual = CostFlow::CreateResidual(g, &F);
   
      //Step 3: F augmenting cycle
      cycle = CostFlow::GetNegativeCycle(*residual);
      
      if( cycle->empty())
         break;
      
      min = MinFromPath(cycle,&F);
     
      //Step 4: update flow
      UpdateFlow(cycle, &F, min);
      //Step 5: Repeat
   }
   double cost = CalculateCost(&g->edges_, &F);
   std::cout << cost << std::endl;
   return true;
   
}


bool CostFlow::compute_b_flow(Graph g,  std::vector<std::vector<double>>* flow){
   
   //compute flow for super source/target
   std::vector<Node * > src_trgt = std::vector<Node*>();
   double b;
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
   // TODO return fuer ungleiche balance
   int src_node = g.AddNode(src_flow);
   int target_node = g.AddNode(target_flow);
   
   for(auto node : src_trgt){
      
      b = node->_balance;
      if (b > 0 )
         g.AddEdge(src_node, node->id_, 0, b);
      else
         g.AddEdge(node->id_, target_node, 0, b * -1);
   }
   
   double max_flow = Flow::EdmondsKarp(&g, g.nodes_[src_node], g.nodes_[target_node], flow);
   return max_flow == src_flow;
}


bool CostFlow::SuccessiveShortestPath(Graph* g ) {
   
   int size = g->Size();
   std::vector<std::vector<double>> F(size, std::vector<double>(size));
   std::vector<double> Bs(size);
   
   //Init 1: Set initial flow on negative edges
   int f, t;
   for (auto e : g->edges_) {
      f = e->from_->id_;
      t = e->to_->id_;
      if (e->weight_ < 0){
         F[f][t] = e->capacity_;
         F[t][f] = (-1) * e->capacity_;
      }
   }
   //Init 2: Create residualgraph and calculate b'(v)
   double d_in, d_out;
   std::vector<Node *> src_list = std::vector<Node *>();
   std::vector<Node *> trgt_list = std::vector<Node *>();
   Graph *residual;
   Node *s, *target;
   double bs, bt;
   auto C = g->GetCapacityMatrix();
   while (true) {
   
      residual = CostFlow::CreateResidual(g,&F);
      src_list.clear();
      trgt_list.clear();
      for (int i = 0; i < size; i++) {
         d_in = 0;
         d_out = 0;
         for (auto o : F[i])
            d_out += (o > 0) ? o : 0;
         for (auto f_i : F)
            d_in += (f_i[i] > 0) ? f_i[i] : 0;
         
         Bs[i] = d_out - d_in;
         if ( g->nodes_[i]->_balance > Bs[i])
            src_list.emplace_back(residual->nodes_[i]);
         else if (g->nodes_[i]->_balance < Bs[i])
            trgt_list.emplace_back(residual->nodes_[i]);
      }
      
      //Step 1: Select Source and target based on b(s/t) - b'(s/t) != 0
      // b(v) is based on g and b'(v) on residual
      
      if (src_list.empty() || trgt_list.empty())
         break;
      
      bool found_st = false;
      s = nullptr; target = nullptr;
      for (auto src : src_list) {
         for (auto trgt: trgt_list) {
            if (Flow::FlowBSF(residual, C, F, src, trgt)) {
               s = src;
               target = trgt;
               found_st = true;
               break;
            }
         }
         if (found_st)
            break;
      }
      if (!s || !target )
         break;
      //Step 2: Calculate shortest Path in residual
      SP::BellmanFord(residual, s);
      auto* sp = new  std::vector<Edge*>();
      PathFromPredecessor(target, s, sp);
      bs = s->_balance - Bs[s->id_];
      bt = target->_balance - Bs[target->id_];
      double min = MinFromPath(sp, &F);
      
      min = std::min(min, std::min(bs, (bt < 0) ? bt * (-1) : bt ));
      
      //Step 3: Update flow
      UpdateFlow(sp, &F, min);
   }
   for(auto node : g->nodes_){
      if(node->_balance != Bs[node->id_])
         return false;
   }
   
   double cost = CalculateCost(&g->edges_, &F);
   std::cout << cost << std::endl;
   return true;
}