//
// Created by mhenn on 5/1/2021.
//

#ifndef MMI_P1_H
#define MMI_P1_H
#include "../Utility/Reader.h"
#include "../Algorithms/Search.h"
#include "../Algorithms/MST.h"
#include "../Algorithms/TSP.h"
#include <filesystem>

void ExecP1(){
   
   Reader r = Reader();
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto& dirEntry : recursive_directory_iterator("../graphs/p1/")) {
      std::filesystem::path file = dirEntry.path();
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph* g = r.ReadFile(f, simple);
      Search s = Search();
      int n = s.ConnectedComponent(g);
      std::cout << n <<std::endl;
   }


}

void ExecP2(){
   
   Reader r = Reader();
   MST mst = MST();
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto& dirEntry : recursive_directory_iterator("../graphs/p2/")) {
      std::filesystem::path file = dirEntry.path();
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph* g = r.ReadFile(f, weighted);
      Graph* m = mst.Kruskal(g);
      double sum = 0;
      std::cout << m->weight_sum_ << std::endl;
   }
}

void ExecP3(){
   
   Reader r = Reader();
   TSP t = TSP();
   int bound = 6;
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto& dirEntry : recursive_directory_iterator("../graphs/p3/")) {
      bound--;
      if(bound == 0)
         return;
      std::filesystem::path file = dirEntry.path();
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph* g = r.ReadFile(f, weighted);
      //Graph* tsp = t.NearestNeighbour(g);
      //Graph* tsp = t.DoubleTree(g);
      Graph* tsp = t.BranchNBound(g);
      //std::cout << tsp->weight_sum_ << std::endl;
   }
}

#endif //MMI_P1_H
