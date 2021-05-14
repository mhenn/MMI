//
// Created by mhenn on 5/14/2021.
//

#ifndef MMI_SP_H
#define MMI_SP_H


#include "../Structures/Graph.h"
#include <functional>
#include <queue>

typedef std::pair<double, Node*> valued_node;


class SP {
      
      
      static void OutputShortestPath(Graph *g, Node *dst);
   
   public:
      static Graph *Dijkstra(Graph *g, Node *start);
      static Graph *BellmanFord(Graph *g, Node *start);
};


#endif //MMI_SP_H
