cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(
    base64
    VERSION 0.1
    DESCRIPTION "Implementation of base64"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

add_executable(base64 ./src/main.cpp)

target_compile_features(base64 PRIVATE cxx_std_17)
