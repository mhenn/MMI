//
// Created by mhenn on 4/30/2021.
//

#include "TSP.h"

Graph *TSP::NearestNeighbour(Graph *g, bool print) {
   g->ClearMarkings();
   int node_count = g->nodes_.size();
   auto tsp = new Graph(node_count);
   Edge *shortest = nullptr;
   Node *current = g->nodes_.at(0);
   current->marked_ = true;
   if (print)
      std::cout << current->id_ << " ";
   while (tsp->edges_.size() != tsp->nodes_.size() - 1) {
      shortest = nullptr;
      for (auto edge : current->edges_)
         if (!edge->to_->marked_)
            if (!shortest || shortest->weight_ > edge->weight_)
               shortest = edge;
      
      tsp->AddEdge(shortest);
      current = shortest->to_;
      current->marked_ = true;
      if(print)
         std::cout << current->id_ << " ";
   }
   
   Edge* final_edge = g->adjacency_matrix_[shortest->to_->id_][0];
   tsp->AddEdge(final_edge);
   return tsp;
}

void TSP::BruteForceRecursion(int* lvl,int* start_id, Node* curr, double sum, double* l_bound, std::vector<Edge*>* tour, std::vector<Edge*>* best_tour, Graph* g, bool* test_all){

   curr->marked_ = true;
  
   double new_sum;
   
   //if(tour->size() == g->nodes_.size() -1){
   if(*lvl == g->nodes_.size()-1){
      Edge* cycle_edge = g->adjacency_matrix_[curr->id_][*start_id];
      double tour_weight = sum + cycle_edge->weight_;
      if(tour_weight < *l_bound){
         *best_tour = *tour;
         best_tour->push_back(cycle_edge);
         *l_bound = tour_weight;
      }
   } else {
      for (auto edge : curr->edges_) {
         new_sum = sum + edge->weight_;
      
         if (!*test_all && new_sum >= *l_bound || edge->to_->marked_)
            continue;
         
         tour->at(*lvl) = edge;
         *lvl+=1;
         BruteForceRecursion(lvl,start_id, edge->to_, new_sum, l_bound, tour, best_tour, g, test_all);
         *lvl-=1;
      }
   }
   curr->marked_ = false;
}

Graph* TSP::BranchNBound(Graph *g, bool test_all) {
   Graph* tsp;
   double l_bound = INFINITY;
   std::vector<Edge*> tour(g->nodes_.size() -1, nullptr);
   std::vector<Edge*> best_tour = std::vector<Edge*>();
   double sum = 0;
   Node* node = g->nodes_[0];
   int lvl = 0;
   g->ClearMarkings();
   BruteForceRecursion(&lvl,&node->id_, node, sum, &l_bound, &tour, &best_tour, g, &test_all);
   
   tsp = new Graph(g->nodes_.size());
   std::cout << best_tour[0]->from_->id_ << " ";
   for(Edge* edge : best_tour){
      tsp->AddEdge(edge);
      std::cout << edge->to_->id_ << " ";
   }
   std::cout << std::endl;
   
   
   return tsp;
}

Graph *TSP::DoubleTree(Graph *g, bool print) {
   MST mst = MST();
   Search search = Search();
   g->ClearMarkings();
   Graph *mst_g = mst.Kruskal(g);
   mst_g->ClearMarkings();
   Edge* current;
   std::vector<Node *> tsp_tour = search.Dfs(mst_g, mst_g->nodes_.at(0));
   auto tsp = new Graph(g->nodes_.size());
   double weight = 0;
   for (unsigned int i = 0, j = 1; j < tsp_tour.size(); i++, j++) {
      int first = tsp_tour[i]->id_;
      int sec = tsp_tour[j]->id_;
      weight = g->adjacency_matrix_[first][sec]->weight_;
      tsp->AddEdge(new Edge(tsp->nodes_[first], tsp->nodes_[sec], weight));
      if(print)
         std::cout << tsp_tour[i]->id_ << " ";
   }
   int f = tsp_tour.back()->id_;
   int s = tsp_tour[0]->id_;
   weight = g->adjacency_matrix_[f][s]->weight_;
   tsp->AddEdge(new Edge(tsp->nodes_[f], tsp->nodes_[s], weight));
   
   
   if(print)
      std::cout << tsp_tour[tsp_tour.size() - 1]->id_ << std::endl;
   return tsp;
}
