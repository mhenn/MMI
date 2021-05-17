//
// Created by mhenn on 5/14/2021.
//

#include <stack>
#include "SP.h"

bool CompareNodesByDist(Node *e, Node *b) {
   return e->dist_ > b->dist_;
}

Graph *SP::Dijkstra(Graph *g, Node *start) {
   
   g->Clear();
   std::priority_queue<Node *, std::vector<Node *>, std::function<bool(Node *, Node *)>> pq(CompareNodesByDist);
   pq.push(start);
   start->dist_ = 0;
   double curr_val;
   Node *curr, *dst;
   int vertice_count = 0;
   
   while(vertice_count != g->Size()){
      curr = pq.top();
      pq.pop();
      
      if (curr->marked_)
         continue;
      
      vertice_count++;
      curr->marked_ = true;
      for (auto e : curr->edges_) {
         curr_val = e->weight_ + curr->dist_;
         dst = e->to_;
         if (curr_val < dst->dist_) {
            dst->parent_ = e->from_;
            dst->dist_ = curr_val;
            pq.push(dst);
         }
      }
   }
   
   return g;
}

Graph *SP::BellmanFord(Graph *g, Node *start) {
   
   g->Clear();
   std::vector<double> dist(g->Size(), 0);
   start->dist_ = 0;
   Node *from, *to;
   double weight;
   
   for (int i = 0; i < g->Size(); i++) {
      for (auto e : g->edges_) {
         from = e->from_;
         to = e->to_;
         weight = e->weight_;
         if (from->dist_ != INFINITY && from->dist_ + weight < to->dist_) {
            to->dist_ = from->dist_ + weight;
            to->parent_ = from;
         }
      }
   }
   
   for (auto e: g->edges_) {
      from = e->from_;
      to = e->to_;
      weight = e->weight_;
      if (from->dist_ + weight < to->dist_) {
         return nullptr;
      }
      
      
   }
   
   return g;
}

void SP::OutputShortestPath(Graph *g, Node *dst) {
   
   std::stack<Node *> q;
   Node *curr = dst;
   std::string ap = " -> ";
   while (curr != curr->parent_) {
      q.push(curr);
      curr = curr->parent_;
   }
   q.push(curr);
   while (!q.empty()) {
      if (q.size() == 1)
         ap = " ";
      std::cout << q.top()->id_ << ap;
      q.pop();
   }
   
   std::cout << "dist: " << dst->dist_ << std::endl;
}
