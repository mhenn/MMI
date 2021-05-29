//
// Created by mhenn on 4/28/2021.
//

#ifndef MMI_GRAPH_H
#define MMI_GRAPH_H

#include <vector>
#include "Node.h"
#include "Edge.h"
#include <algorithm>
#include <iterator>
#include <map>

enum DIR {
   DIRECTED, UNDIRECTED
};

class Graph {
   public:
      std::vector<Node *> nodes_;
      std::vector<Edge *> edges_;
      std::map<int, std::vector<Node *>> adjacency_;
      
      double weight_sum_ = 0;
   public:
      Graph();
      
      explicit Graph(int size);
      
      int Size(){return nodes_.size();}
      
      void AddEdge(Edge *edge, bool add_weight = true);
      
      void AddAdjacency(Edge *edge);
      
      void AddEdge(int from, int to, DIR type);
      
      void AddEdge(int from, int to, double weight, DIR type);
      
      void ClearMarkings();
      
      Edge *GetEdge(Node *from, Node *to);
      
      Edge *GetEdge(int from, int to);
      
      void Clear();
      
      void ClearEdges();
      
      std::vector<Edge*>* GetAllEdgesTo(Node* rome);
      
      void BuildResidual();
};

#endif //MMI_GRAPH_H