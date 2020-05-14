cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(PROJECT_NAME fct_read)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #allows use of filesystem
set(CMAKE_CXX_FLAGS "-pthread -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g")

set(INCLUDE_DIRS modules/fct_read/include/)

add_subdirectory(modules)
add_subdirectory(applications)

