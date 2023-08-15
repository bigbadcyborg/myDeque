cmake_minimum_required(VERSION 3.12)
project(dequeue)

set(CMAKE_CXX_STANDARD 98)

add_executable(dequeue proj9-driver.cpp proj9-MyDeque.h proj9-ContainerIfc.h)