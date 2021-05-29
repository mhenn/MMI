//
// Created by mhenn on 5/14/2021.
//

#ifndef MMI_SP_H
#define MMI_SP_H


#include "../Structures/Graph.h"
#include <functional>
#include <queue>
#include <iostream>

typedef std::pair<double, Node*> valued_node;


class SP {
   
   public:
      static void OutputShortestPath(Graph *g, Node *dst);
      static Graph *Dijkstra(Graph *g, Node *start);
      static Graph *BellmanFord(Graph *g, Node *start);
};


#endif //MMI_SP_H
