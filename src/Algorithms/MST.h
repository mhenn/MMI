//
// Created by mhenn on 4/30/2021.
//

#ifndef MMI_MST_H
#define MMI_MST_H
#include "../Structures/Graph.h"
#include <functional>
#include <queue>
class MST {

   public:
      Graph* Prim(Graph* g, Node* start);
   Graph* Kruskal(Graph* g);
   private:
      Node* Find(Node* n);
      void Union(Node* n1, Node* n2);
};


#endif //MMI_MST_H
