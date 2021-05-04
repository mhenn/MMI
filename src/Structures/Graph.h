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

class Graph {
   public:
      std::vector<Node*> nodes_;
      std::vector<Edge*> edges_;
      std::map<int, std::vector<Node*>> adjacency_;
      std::vector<std::vector<Edge*>> adjacency_matrix_;
      double weight_sum_ = 0;
   public:
      Graph();
      Graph(int size);
      
      void AddEdge(Edge* edge);
      
      void AddNode(Node* node);
      
      void AddAdjacency(Edge *edge);
      
      void AddEdge(int from, int to);
      
      void AddEdge(int from, int to, double weight);

      void ClearMarkings();
      
      void RemoveEdge(Edge *edge);
      
      void AddAdjacencyMatrix(Edge *edge);
};

#endif //MMI_GRAPH_H