cmake_minimum_required(VERSION 3.12)
project(turing C)

set(CMAKE_C_STANDARD 11)

add_executable(turing main/main.c headers/t_machine.h headers/common.h sources/common.c sources/t_machine.c)