//
// Created by mhenn on 4/29/2021.
//

#include <sstream>
#include "Reader.h"
#include <string>

Graph* Reader::ReadFile(const std::string& file_name, Graph_type type) {
   std::ifstream file(file_name);
   Graph* g;
   std::string line;
   int from_id ,to_id;
   double weight, cap;
   bool init = true;
   int node_count = 0;
   int b_pos = 0;
   Edge* e = nullptr;
   while(std::getline(file,line )){
      std::stringstream sline(line);
      std::string token;
      if(init) {
         int size;
         sline >> size;
         node_count = size;
         g = new Graph(size);
         init = false;
         continue;
      }
      
      if(type == simple){
         sline >> from_id >> to_id;
         g->AddEdge(from_id, to_id, UNDIRECTED);
      } else if(type == weighted){
         sline >> from_id >> to_id >> weight;
         g->AddEdge(from_id, to_id, weight, UNDIRECTED);
      } else if(type == weighted_directed ){
         sline >> from_id >> to_id >> weight;
         g->AddEdge(from_id, to_id, weight, DIRECTED);
      } else if(type == capacity) {
         sline >> from_id >> to_id >> weight;
         g->AddEdge(from_id, to_id, 0, weight);
      } else if(type == balance){
         if(node_count != b_pos){
            sline >> weight;
            g->nodes_[b_pos++]->_balance = weight;
         } else{
            sline >> from_id >> to_id >> weight >> cap;
            g->AddEdge(from_id, to_id, weight, cap);
         }
      }
   }
   return g;
}