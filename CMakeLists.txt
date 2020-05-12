cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(PROJECT_NAME fct_read)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #allows use of filesystem
set(CMAKE_CXX_FLAGS "-pthread -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g")

# Third party
#set(3RDPARTYDIR 3rdParty)
#add_subdirectory(${3RDPARTYDIR}/OpenMesh-8.0/)

file( GLOB SOURCES src/*.cpp )

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)  
#target_link_libraries(${PROJECT_NAME})

