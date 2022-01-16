cmake_minimum_required(VERSION 3.20)
project(273CompanyWork)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_executable(273CompanyWork main.cpp)
