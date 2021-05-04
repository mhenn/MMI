//
// Created by mhenn on 4/28/2021.
//

#include "Graph.h"

Graph::Graph(){
   nodes_ =  std::vector<Node*>();
   edges_ =  std::vector<Edge*>();
   adjacency_ = std::map<int, std::vector<Node*>>();
   adjacency_matrix_ = std::vector<std::vector<Edge*>>();
}

Graph::Graph(int size){
   nodes_ = std::vector<Node*>();
   for(int i = 0; i < size; i++)
      nodes_.push_back(new Node(i));
   edges_ = std::vector<Edge*>();
   adjacency_ = std::map<int, std::vector<Node*>>();
   adjacency_matrix_.resize(size, std::vector<Edge*>(size,nullptr));
}

void Graph::AddEdge(int from, int to) {
   AddEdge(new Edge(nodes_.at(from), nodes_.at(to)));
   AddEdge(new Edge(nodes_.at(to), nodes_.at(from)));
}

void Graph::AddEdge(int from, int to, double weight) {
   AddEdge(new Edge(nodes_.at(from), nodes_.at(to), weight));
   AddEdge(new Edge(nodes_.at(to), nodes_.at(from), weight));
}

//TODO splitt into AddWeightedEdge
void Graph::AddEdge(Edge* edge){
   edges_.push_back(edge);
   nodes_.at(edge->from_->id_)->AddEdge(edge);
   weight_sum_ += edge->weight_;
   AddAdjacency(edge);
   AddAdjacencyMatrix(edge);
}

void Graph::RemoveEdge(Edge *edge){
   edges_.erase(std::remove(edges_.begin(), edges_.end(),edge),edges_.end());
}

void Graph::AddNode(Node* node){
   nodes_.push_back(node);
}
//TODO both shouldnt add both directions, make it AddEdge dependant
void Graph::AddAdjacency(Edge* edge){
   adjacency_[edge->from_->id_].push_back(edge->to_);
   adjacency_[edge->to_->id_].push_back(edge->from_);
}
void Graph::AddAdjacencyMatrix(Edge* edge){
   adjacency_matrix_[edge->from_->id_][edge->to_->id_] = edge;
   adjacency_matrix_[edge->to_->id_][edge->from_->id_] = edge;
}

void Graph::ClearMarkings(){
   for(auto n : nodes_)
      n->marked_ = false;
}

