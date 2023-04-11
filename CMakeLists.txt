cmake_minimum_required(VERSION 3.13)  # CMake version check
project(source_boilerplate)               # Create project
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES app/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(source_boilerplate ${SOURCE_FILES})