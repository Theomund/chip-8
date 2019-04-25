cmake_minimum_required(VERSION 3.12)
project(chip-8)
set(SOURCES include/cpu.h
            include/emulator.h
            include/memory.h
            include/keyboard.h
            include/font.h
            include/display.h
            include/sound.h
            src/memory.cpp
            src/main.cpp
            src/cpu.cpp
            src/emulator.cpp
            src/keyboard.cpp
            src/font.cpp
            src/display.cpp
            src/sound.cpp)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "./cmake")
find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
