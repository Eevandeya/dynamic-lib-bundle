cmake_minimum_required(VERSION 3.30)
project(func_eval)

set(CMAKE_CXX_STANDARD 20)

add_library(func_eval SHARED func_eval.cpp func_eval)
