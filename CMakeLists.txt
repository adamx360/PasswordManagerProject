cmake_minimum_required(VERSION 3.22)
project(project2)

set(CMAKE_CXX_STANDARD 20)

add_executable(project2 main.cpp Password.h ObjectOperations.h ObjectOperations.cpp Password.cpp Category.cpp Category.h FileOperations.cpp FileOperations.h)
