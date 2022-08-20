cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(container VERSION 0.1 LANGUAGES C)

add_library(linear_list OBJECT linear_list.h linear_list.c)
add_library(stack OBJECT stack.h stack.c)
add_library(queue OBJECT queue.h queue.c)
