cmake_minimum_required(VERSION 2.6)
project(CmdLineOptions)

set(CMAKE_CXX_FLAGS "--std=c++14 -g -Wall")
add_library(CmdLineOptions_static STATIC CmdLineOptions.cpp)
add_library(CmdLineOptions SHARED CmdLineOptions.cpp)
