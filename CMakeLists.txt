# cmake_minimum_required(VERSION <specify CMake version here>)
project(PEA)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(PEA main.cpp Algorithms.cpp Algorithms.h Data.cpp Data.h Test.cpp Test.h)