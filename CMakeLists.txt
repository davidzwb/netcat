cmake_minimum_required(VERSION 2.8)

project(netcat)

file(GLOB netcat_sources *.cpp *.h netcat-src/*.cpp)
add_executable(netcat ${netcat_sources})
target_compile_options(netcat PUBLIC -std=c++11 -Wall -Wfloat-conversion)
