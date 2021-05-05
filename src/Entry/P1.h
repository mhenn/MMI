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

void ExecP3(int bound, int alg){
   
   Reader r = Reader();
   TSP t = TSP();
   Graph * tsp;
   //Graph*
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto& dirEntry : recursive_directory_iterator("../graphs/p3/")) {
      bound--;
      if(bound == 0)
         return;
      std::filesystem::path file = dirEntry.path();
      
      
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph* g = r.ReadFile(f, weighted);
      auto start = std::chrono::system_clock::now();
      switch(alg){
         case 1:
            tsp = TSP::NearestNeighbour(g,true);
            break;
         case 2:
            tsp = TSP::DoubleTree(g, true);
            break;
         case 3:
            tsp = TSP::BranchNBound(g,false);
            break;
         case 4:
            tsp = TSP::BranchNBound(g,true);
            break;
         default:
            break;
      }
      auto end = std::chrono::system_clock::now();
      auto elapsed =end - start;
      auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed);
      std::cout <<  "time:" << f_secs << '\n';
      std::cout <<  "weight:" << tsp->weight_sum_ << std::endl;
      std::cout << std::endl;
   }
}

#endif //MMI_P1_H
