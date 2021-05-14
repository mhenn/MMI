//
// Created by mhenn on 4/30/2021.
//

#include "Search.h"


std::vector<Node*> Search::Bfs(Graph* g, Node* start ){
   start->marked_ = true;
   std::queue<Node*> queue = std::queue<Node*>();
   queue.push(start);
   std::vector<Node*> visited = std::vector<Node*>();
   visited.push_back(start);
   
   while(!queue.empty()){
      Node* node = queue.front();
      queue.pop();
      for(Node* d : g->adjacency_[node->id_]){
         if(!d->marked_){
            d->marked_ = true;
            queue.push(d);
            visited.push_back(d);
         }
      }
   }
   return visited;
}
std::vector<Node *> Search::Dfs(Graph* g, Node* start){
   start->marked_ = true;
   std::stack<Node*> stack = std::stack<Node*>();
   stack.push(start);
   std::vector<Node*> visited = std::vector<Node*>();
   
   while(!stack.empty()){
      Node* node = stack.top();
      visited.push_back(node);
      stack.pop();
      for(auto e : node->edges_){
         Node* d = e->to_;
         if(!d->marked_){
            d->marked_ = true;
            stack.push(d);
         }
      }
   }
   return visited;
}

int  Search::ConnectedComponent(Graph * g){
   
   int components = 0;
   
   for( Node* n: g->nodes_ ){
      if(!n->marked_){
         components++;
         Dfs(g, n);
      }
   }
   return components;
}
