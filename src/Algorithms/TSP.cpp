//
// Created by mhenn on 4/30/2021.
//

#include "TSP.h"

Graph *TSP::NearestNeighbour(Graph *g) {
   g->ClearMarkings();
   int node_count = g->nodes_.size();
   auto tsp = new Graph(node_count);
   
   Node *current = g->nodes_.at(0);
   current->marked_ = true;
   std::cout << current->id_ << " ";
   while (tsp->edges_.size() != tsp->nodes_.size() - 1) {
      Edge *shortest = 0;
      for (auto edge : current->edges_)
         if (!edge->to_->marked_)
            if (!shortest || shortest->weight_ > edge->weight_)
               shortest = edge;
      
      tsp->AddEdge(shortest);
      current = shortest->to_;
      current->marked_ = true;
      std::cout << current->id_ << " ";
   }
   
   auto IsId = [](Edge *e) { return e->to_->id_ == 0; };
   auto final_edge = std::find_if(current->edges_.begin(), current->edges_.end(), IsId);
   tsp->AddEdge(*final_edge);
   return tsp;
}

void TSP::BruteForceRecursion(int* start_id, Node* curr, double sum, double* l_bound, std::vector<Node*>* tour, std::vector<Node*>* best_tour, Graph* g){

   curr->marked_ = true;
   
   double new_sum;
   for(auto edge : curr->edges_){
      new_sum = sum + edge->weight_;
      
      if(new_sum >= *l_bound || edge->to_->marked_)
         continue;
      tour->push_back(edge->to_);
      BruteForceRecursion(start_id, edge->to_, new_sum, l_bound, tour, best_tour,  g );
      tour->pop_back();
   }
   
   if(tour->size() == g->nodes_.size()){
   
      Edge* cycle_edge = g->adjacency_matrix_[curr->id_][*start_id];
      double tour_weight = sum + cycle_edge->weight_;
      if(tour_weight < *l_bound){
         *best_tour = *tour;
         *l_bound = tour_weight;
      }
   }
   
   curr->marked_ = false;
}

Graph* TSP::BranchNBound(Graph *g) {
  
   Graph* tsp = NearestNeighbour(g);
   double l_bound = tsp->weight_sum_;
   std::vector<Node*> tour = std::vector<Node*>();
   std::vector<Node*> best_tour = std::vector<Node*>();
   double sum = 0;
   for(auto node : g->nodes_) {
      tour.push_back(node);
      BruteForceRecursion(&node->id_, node, sum, &l_bound, &tour, &best_tour, g);
      tour.pop_back();
   }
   std::cout << l_bound << std::endl;
   return nullptr;
}

////TODO getting all branches works, next is the comparison between them to get the best. Also the level above to change the lower bound
//Graph *TSP::BranchNBound(Graph *g, int i ) {
//   int graph_size = g->nodes_.size();
//   Graph *tour = NearestNeighbour(g);
//   double l_bound = tour->weight_sum_;
//   std::stack<leveled_node> stack = std::stack<leveled_node>();
//   std::vector<Node*> best = std::vector<Node*>();
//   std::vector<Node *> latest = std::vector<Node *>();
//   Node *last, *tmp_node;
//   leveled_node tmp;
//   int level;
//   bool lvl = false;
//   double sum;
//   for (auto node : g->nodes_) {
//      sum = 0;
//      level = 0;
//      last = 0;
//      g->ClearMarkings();
//      latest.clear();
//      stack.push(leveled_node(node, level++, sum));
//      while (!stack.empty()) {
//         tmp = stack.top();
//         if(last && last->rank_ == tmp.level_ && last != tmp.node_){
//            last->marked_ = false;
//            last->rank_ = 0;
//            latest.pop_back();
//         }
//         latest.push_back(tmp.node_);
//         stack.pop();
//         if (tmp.level_ == graph_size - 1) {
//            //auto edge = find_if(g->edges_.begin(), g->edges_.end(), [&](Edge* e){return e->from_->id_ == node->id_ && e->to_->id_ == last->id_; });
//            sum = tmp.weight_ + g->adjacency_matrix_[node->id_][last->id_];
//
//            if (sum < l_bound) {
//               l_bound = sum;
//               tmp_node = last;
//               best = latest;
//            }
//            continue;
//         }
//         if (last && tmp.level_ < last->rank_) {
//
//            for(int i = tmp.level_+1; i < latest.size(); i++){
//               latest[i]->marked_ = false;
//               latest[i]->rank_ = 0;
//            }
//            level = tmp.level_;
//            latest.erase(latest.begin()  + ++level, latest.end());
//         }
//         tmp.node_->marked_ = true;
//         for (auto e: tmp.node_->edges_) {
//            sum = tmp.weight_ + e->weight_;
//            if (!e->to_->marked_ && sum < l_bound) {
//               lvl = true;
//               stack.push(leveled_node(e->to_, level, sum));
//               e->to_->rank_ = level;
//               last = e->to_;
//            }
//         }
//         if (lvl)
//            level++;
//         lvl = false;
//      }
//   }
//   std::cout << l_bound;
//   return nullptr;
//}
//

Graph *TSP::DoubleTree(Graph *g) {
   MST mst = MST();
   Search search = Search();
   Graph *mst_g = mst.Kruskal(g);
   std::vector<Node *> tsp_tour = search.Dfs(mst_g, mst_g->nodes_.at(0));
   auto tsp = new Graph(g->nodes_.size());
   
   for (int i = 0, j = 1; j < tsp_tour.size(); i++, j++) {
      int first = tsp_tour[i]->id_;
      int sec = tsp_tour[j]->id_;
      
      auto edge = find_if(g->edges_.begin(), g->edges_.end(),
                          [&](Edge *e) { return e->from_->id_ == first && e->to_->id_ == sec; });
      tsp->AddEdge(*edge);
      tsp->RemoveEdge(*edge);
      std::cout << tsp_tour[i]->id_ << " ";
   }
   std::cout << tsp_tour[tsp_tour.size() - 1]->id_ << std::endl;
   return tsp;
}
