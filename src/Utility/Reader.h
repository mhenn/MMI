//
// Created by mhenn on 4/29/2021.
//

#ifndef MMI_READER_H
#define MMI_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include "../Structures/Graph.h"

enum Graph_type { simple, weighted, weighted_directed};

class Reader {
   public:
      
      static Graph *ReadFile(std::string file_name, Graph_type type);
      
};


#endif //MMI_READER_H
