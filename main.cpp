#include "src/Entry/P1.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
  
   std::string t = argv[1];
   if(t == "1")
      ExecP1();
   else if(t == "2")
      ExecP2();
   else if(t == "3")
      ExecP3(atoi(argv[2]), atoi(argv[3]));
   return 0;
}
