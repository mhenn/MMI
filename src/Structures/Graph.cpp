//
// Created by mhenn on 4/28/2021.
//

#include "Graph.h"

Graph::Graph(){
   nodes_ =  std::vector<Node*>();
   edges_ =  std::vector<Edge*>();
   adjacency_ = std::map<int, std::vector<Node*>>();
}

Graph::Graph(int size){
   nodes_ = std::vector<Node*>();
   for(int i = 0; i < size; i++)
      nodes_.push_back(new Node(i));
   edges_ = std::vector<Edge*>();
   adjacency_ = std::map<int, std::vector<Node*>>();
}



void Graph::AddEdge(int from, int to, DIR type) {
   AddEdge(new Edge(nodes_.at(from), nodes_.at(to)), false);
   if(type == UNDIRECTED)
      AddEdge(new Edge(nodes_.at(to), nodes_.at(from)), true);
}

void Graph::AddEdge(int from, int to, double weight, double capacity){
   Edge *edge = new Edge(nodes_.at(from), nodes_.at(to), weight);
   edge->capacity_ = capacity;
   AddEdge(edge, true);
}

void Graph::AddEdge(int from, int to, double weight, double capacity, bool residual){
   Edge *edge = new Edge(nodes_.at(from), nodes_.at(to), weight);
   edge->capacity_ = capacity;
   edge->residual = residual;
   AddEdge(edge, true);
}

void Graph::AddEdge(int from, int to, double weight, DIR type) {
   AddEdge(new Edge(nodes_.at(from), nodes_.at(to), weight), true);
   if(type == UNDIRECTED)
      AddEdge(new Edge(nodes_.at(to), nodes_.at(from), weight), false);
}

void Graph::AddEdge(Edge* edge, bool add_weight){
   edges_.emplace_back(edge);
   nodes_.at(edge->from_->id_)->AddEdge(edge);
   if(add_weight)
      weight_sum_ += edge->weight_;
   AddAdjacency(edge);
}

int Graph::AddNode(double balance){
   int pos = nodes_.size();
   nodes_.emplace_back(new Node(pos));
   nodes_[pos]->_balance = balance;
   return pos;
}


void Graph::AddAdjacency(Edge* edge){
   adjacency_[edge->from_->id_].push_back(edge->to_);
}

void Graph::ClearMarkings(){
   for(auto n : nodes_)
      n->marked_ = false;
}

void Graph::Clear(){
   for(auto n: nodes_){
      n->marked_ = false;
      n->parent_ = n;
      n->rank_ = 0;
      n->dist_ = INFINITY;
   }
}

void Graph::ClearEdges(){
   for(auto e: edges_) {
      e->weight_ = 0;
   }
}

std::vector< std::vector< double>>  Graph::GetCapacityMatrix(){
   
   unsigned int size = nodes_.size();
   std::vector<std::vector<double>> adj_matrix(size, std::vector<double>(size, 0));
   for(auto e : edges_)
      adj_matrix[e->from_->id_][e->to_->id_] = e->capacity_;
   
   return adj_matrix;
}

/*
void Graph::BuildResidual(){
   std::vector<Edge*> new_res = std::vector<Edge*>();
   std::vector<Edge*> removals = std::vector<Edge*>();
   Edge* e;
   for(auto e : edges_){
      if(e->CapacityRemainder() == 0) {
         removals.emplace_back(e);
         continue;
      }
      if (e->weight_ != 0 && !e->is_residual_){
         auto existing_res_edge = GetEdge(e->to_,e->from_);
         if (existing_res_edge ){
            existing_res_edge->capacity_ = e->weight_;
         } else {
            Edge *new_residual = new Edge(e->to_, e->from_, false);
            new_residual->is_residual_ = true;
            new_residual->capacity_ = e->weight_;
            new_res.emplace_back(new_residual);
         }
      }
   }
   for (auto i : removals)
      edges_.erase(std::remove(edges_.begin(), edges_.end(), i), edges_.end());
   for(auto e : new_res)
      AddEdge(e,false);
}
*/

Edge* Graph::GetEdge(Node* from, Node* to){
   auto it = std::find_if(from->edges_.begin(), from->edges_.end(), [&](Edge* e){return e->to_->id_ == to->id_;});
   if(it != from->edges_.end())
      return *it;
   return nullptr;
}

Edge* Graph::GetEdge(int from, int to) {
   return GetEdge(nodes_[from], nodes_[to]);
}
