//
// Created by mhenn on 4/30/2021.
//

#ifndef MMI_SEARCH_H
#define MMI_SEARCH_H
#include <stack>
#include <queue>
#include "../Structures/Graph.h"

class Search {

   public:
      std::vector<Node *> Bfs(Graph* g, Node* start);
      std::vector<Node *> Dfs(Graph* g, Node* start);
      int  ConnectedComponent(Graph * g);
      
};


#endif //MMI_SEARCH_H
