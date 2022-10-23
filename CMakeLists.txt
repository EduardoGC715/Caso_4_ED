cmake_minimum_required(VERSION 3.21)

project(Caso_4_ED)

set(CMAKE_CXX_STANDARD 14)

add_executable(Caso_4_ED
        main.cpp Map/Map.h Map/Room.h Map/Tunnel.h Map/Chamber.h "ADT/AVL_Tree.h" ADT/Tree_Node.h ADT/Point.h utils/Random.h utils/Max.h ADT/Priority_Queue.h)
