# cmake_minimum_required(VERSION <specify CMake version here>)
project(mmi)

set(CMAKE_CXX_STANDARD 20)

add_executable(mmi main.cpp src/Structures/Edge.cpp src/Structures/Edge.h src/Structures/Graph.cpp src/Structures/Graph.h src/Structures/Node.cpp src/Structures/Node.h src/Utility/Reader.cpp src/Utility/Reader.h src/Algorithms/Search.cpp src/Algorithms/Search.h src/Algorithms/MST.cpp src/Algorithms/MST.h src/Algorithms/TSP.cpp src/Algorithms/TSP.h src/Entry/P1.h src/Algorithms/SP.cpp src/Algorithms/SP.h src/Algorithms/Flow.cpp src/Algorithms/Flow.h)