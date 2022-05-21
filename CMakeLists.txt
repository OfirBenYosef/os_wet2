cmake_minimum_required(VERSION 3.22)
project(os_wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(os_wet2 main.cpp Bank.cpp Bank.h lock.cpp lock.h atm.cpp atm.h)
