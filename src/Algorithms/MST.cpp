//
// Created by mhenn on 4/30/2021.
//

#include "MST.h"

Graph* MST::Prim(Graph* g, Node* start){
   
   Graph* mst = new Graph(g->nodes_.size());
   std::map<int,Edge*> map;
   
   return mst;
}

bool Compare(Edge* e, Edge* b){
   return e->weight_ > b->weight_;
}

Graph* MST::Kruskal(Graph* g) {
   
   Graph *mst = new Graph(g->nodes_.size());
   std::priority_queue<Edge *, std::vector<Edge *>, std::function<bool(Edge*,Edge*)> > pq(Compare);
   for(Edge* e : g->edges_)
      pq.push(e);
   
   while (!pq.empty()) {
      Edge *e = pq.top();
      pq.pop();
      if (Find(e->from_) != Find(e->to_)) {
         mst->AddEdge(e->from_->id_, e->to_->id_,e->weight_, UNDIRECTED);
         Union(e->from_, e->to_);
      }
      if (mst->nodes_ == g->nodes_)
         return mst;
   }
   return mst;
}

Node* MST::Find(Node* n){
   
   if(n->parent_->id_ == n->id_)
      return n;
   return Find(n->parent_);
}

void MST::Union(Node* n1, Node* n2){

   Node* p1 = Find(n1);
   Node* p2 = Find(n2);
   
   if(p1->rank_ >= p2->rank_){
      if(p1->rank_ == p2->rank_)
         p1->rank_++;
      p2->parent_ = p1;
   } else
      p1->parent_ = p2;
}