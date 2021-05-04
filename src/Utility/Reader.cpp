//
// Created by mhenn on 4/29/2021.
//

#include <sstream>
#include "Reader.h"
#include <string>

Graph* Reader::ReadFile(std::string file_name, Graph_type type) {
   std::ifstream file(file_name);
   Graph* g;
   std::string line;
   int from_id ,to_id;
   double weight;
   bool init = true;
   while(std::getline(file,line )){
      std::stringstream sline(line);
      std::string token;
      if(init) {
         int size;
         sline >> size;
         g = new Graph(size);
         init = false;
         continue;
      }
      
      if(type == simple){
         sline >> from_id >> to_id;
         g->AddEdge(from_id, to_id);
      } else if(type == weighted){
         sline >> from_id >> to_id >> weight;
         g->AddEdge(from_id, to_id, weight);
      }
   }
   return g;
}