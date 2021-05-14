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
   std::vector<std::vector<Edge*>> tmp(size, std::vector<Edge*>(size, nullptr));
}

void Graph::AddEdge(int from, int to, DIR type) {
   AddEdge(new Edge(nodes_.at(from), nodes_.at(to)), false);
   if(type == UNDIRECTED)
      AddEdge(new Edge(nodes_.at(to), nodes_.at(from)), true);
}

void Graph::AddEdge(int from, int to, double weight, DIR type) {
   AddEdge(new Edge(nodes_.at(from), nodes_.at(to), weight), true);
   if(type == UNDIRECTED)
      AddEdge(new Edge(nodes_.at(to), nodes_.at(from), weight), false);
}

void Graph::AddEdge(Edge* edge, bool add_weight){
   edges_.push_back(edge);
   nodes_.at(edge->from_->id_)->AddEdge(edge);
   if(add_weight)
      weight_sum_ += edge->weight_;
   AddAdjacency(edge);
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

Edge* Graph::GetEdge(Node* from, Node* to){
   auto it = std::find_if(from->edges_.begin(), from->edges_.end(), [&](Edge* e){return e->to_->id_ == to->id_;});
   return *it;
}

Edge* Graph::GetEdge(int from, int to) {
   return GetEdge(nodes_[from], nodes_[to]);
}