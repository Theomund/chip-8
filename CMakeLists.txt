cmake_minimum_required(VERSION 3.14)
project(chip-8)
add_executable(${PROJECT_NAME} include/emulator.h src/main.cpp src/emulator.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
