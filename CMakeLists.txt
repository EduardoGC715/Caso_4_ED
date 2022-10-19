cmake_minimum_required(VERSION 3.21)
project(Caso_4_ED)

set(CMAKE_CXX_STANDARD 14)

add_executable(Caso_4_ED
        Main.cpp Map/Map.h Map/Room.h Map/Tunnel.h Map/Chamber.h "DS/AVL_Tree.h" DS/Tree_Node.h DS/List.h DS/List_Node.h DS/Point.h)
