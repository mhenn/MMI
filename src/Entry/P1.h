//
// Created by mhenn on 5/1/2021.
//

#ifndef MMI_P1_H
#define MMI_P1_H

#include "../Utility/Reader.h"
#include "../Algorithms/Search.h"
#include "../Algorithms/MST.h"
#include "../Algorithms/TSP.h"
#include "../Algorithms/SP.h"
#include <filesystem>
#include "../Algorithms/Flow.h"
#include "../Algorithms/CostFlow.h"

std::vector<std::pair<std::string, Graph *>> GetGraph(std::string path, Graph_type type) {
   std::vector<std::pair<std::string, Graph *>> graphs;
   std::filesystem::path file_path;
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   
   for (const auto &dirEntry : recursive_directory_iterator(path)) {
      file_path = dirEntry.path();
      std::string file_name = file_path.generic_string();
      Graph *g = Reader::ReadFile(file_name, type);
      graphs.emplace_back(file_name, g);
   }
   return graphs;
}

void ExecP1() {
   
   Reader r = Reader();
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto &dirEntry : recursive_directory_iterator("../graphs/p1/")) {
      const std::filesystem::path& file = dirEntry.path();
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph *g = Reader::ReadFile(f, simple);
      Search s = Search();
      int n = s.ConnectedComponent(g);
      std::cout << n << std::endl;
   }
   
   
}

void ExecP2() {
   
   Reader r = Reader();
   MST mst = MST();
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto &dirEntry : recursive_directory_iterator("../graphs/p2/")) {
      const std::filesystem::path& file = dirEntry.path();
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph *g = Reader::ReadFile(f, weighted);
      Graph *m = mst.Kruskal(g);
      double sum = 0;
      std::cout << m->weight_sum_ << std::endl;
   }
}

void ExecP3(int bound, int alg) {
   
   Reader r = Reader();
   TSP t = TSP();
   Graph *tsp;
   //Graph*
   using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
   for (const auto &dirEntry : recursive_directory_iterator("../graphs/p3/")) {
      bound--;
      if (bound == 0)
         return;
      const std::filesystem::path& file = dirEntry.path();
      
      
      std::string f = file.generic_string();
      std::cout << f << std::endl;
      Graph *g = Reader::ReadFile(f, weighted);
      auto start = std::chrono::system_clock::now();
      switch (alg) {
         case 1:
            tsp = TSP::NearestNeighbour(g, true);
            break;
         case 2:
            tsp = TSP::DoubleTree(g, true);
            break;
         case 3:
            tsp = TSP::BranchNBound(g, false);
            break;
         case 4:
            tsp = TSP::BranchNBound(g, true);
            break;
         default:
            break;
      }
      auto end = std::chrono::system_clock::now();
      auto elapsed = end - start;
      auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed);
      std::cout << "time:" << f_secs << '\n';
      std::cout << "weight:" << tsp->weight_sum_ << std::endl;
      std::cout << std::endl;
   }
}

void ExecP4(int alg) {
   Node *dst, *tmp;
   Graph *g;
   Edge* e;
   std::string file_name;
   std::vector<std::pair<std::string,Graph*>> g_list = GetGraph("../graphs/p4", weighted_directed);
   
   for(int i = 0; i < 2; i++) {
   
      for (const auto& p : g_list) {
         e = nullptr;
         file_name = p.first;
         g = p.second;
         dst = g->nodes_[0];
         if (i == 0)
            dst = g->nodes_[2];
         
         tmp = g->nodes_[i];
         std::cout << file_name << std::endl;
         if (alg == 1)
            g = SP::Dijkstra(g, dst);
         else
            e = SP::BellmanFord(g, dst);
      
         if (e)
            std::cout << "Negativer Zyklus" << std::endl;
         else
            SP::OutputShortestPath(g, tmp);
      
      }
      g_list.clear();
      std::string path =  "../graphs/p2/G1_1_2.txt";
      g_list.emplace_back(path,Reader::ReadFile(path, weighted_directed));
      g_list.emplace_back(path, Reader::ReadFile(path, weighted));
   }
   
}

void ExecP5() {
   Node *start, *goal;
   Graph *g;
   std::string file_name;
   std::vector<std::pair<std::string,Graph*>> g_list = GetGraph("../graphs/p5", capacity);
   double flow = 0.0;
   for(int i = 0; i < 2; i++) {
      
      for (const auto& p : g_list) {
         file_name = p.first;
         g = p.second;
         start = g->nodes_[0];
         goal = g->nodes_[7];
         std::cout << file_name << std::endl;
         int size = g->Size();
         std::vector<std::vector<double>> F(size, std::vector<double>(size, 0));
         flow = Flow::EdmondsKarp(g, start, goal, &F);
         
         std::cout << "Max Fluss: " << flow << std::endl;
         
      }
      g_list.clear();
      std::string path =  "../graphs/p2/G1_1_2.txt";
      g_list.emplace_back(path,Reader::ReadFile(path, capacity));
   }
}

void ExecP6(int alg) {
   Graph *g;
   std::string file_name;
   std::vector<std::pair<std::string,Graph*>> g_list = GetGraph("../graphs/p6", balance);
   bool flow;
   
   for (const auto& p : g_list) {
      
      file_name = p.first;
      g = p.second;
      std::cout << file_name << std::endl;
      if (alg == 1) {
         flow = CostFlow::cycle_canceling(g);
      } else
         flow = CostFlow::SuccessiveShortestPath(g);
      if (!flow)
         std::cout << "Kein b-Fluss moeglich" << std::endl;
   }

}

#endif //MMI_P1_H
