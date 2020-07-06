cmake_minimum_required(VERSION 3.15)
project(compilation C)

set(CMAKE_C_STANDARD 99)

add_executable(compilation main.c lex.c syntx.c lex.h syntx.h)