file( GLOB SOURCES src/*.cpp )
add_library(fct_read ${SOURCES})
target_include_directories(fct_read PUBLIC include/)
