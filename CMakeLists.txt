cmake_minimum_required(VERSION 3.13)  # CMake version check
project(progessive_p2p)               # Create project
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/main.cpp)

find_package(raylib 4.5 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(progessive_p2p ${SOURCE_FILES})