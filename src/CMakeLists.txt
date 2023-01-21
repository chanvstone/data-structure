cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(container VERSION 0.1 LANGUAGES C)

add_library(linear_list STATIC)
target_sources(linear_list PUBLIC linear_list.h PRIVATE linear_list.c)
target_include_directories(linear_list PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(linked_list STATIC)
target_sources(linked_list PUBLIC linked_list.h PRIVATE linked_list.c)
target_include_directories(linked_list PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(stack STATIC)
target_sources(stack PUBLIC stack.h PRIVATE stack.c)
target_link_directories(stack PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(queue STATIC)
target_sources(queue PUBLIC queue.h PRIVATE queue.c)
target_link_directories(queue PUBLIC ${CMAKE_CURRENT_LIST_DIR})