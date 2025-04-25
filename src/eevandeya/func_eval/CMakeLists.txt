cmake_minimum_required(VERSION 3.29)
project(. C)

set(CMAKE_C_STANDARD 11)

add_library(func_eval SHARED func_eval.c)
