cmake_minimum_required(VERSION 3.21)
project(Caso_4_ED)

set(CMAKE_CXX_STANDARD 14)

add_executable(Caso_4_ED
        Main.cpp Map.h Room.h Tunnel.h Chamber.h "AVL_Tree.h" Tree_Node.h List.h List_Node.h Point.h)
