cmake_minimum_required(VERSION 3.16)

project(ChessMinimax)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(ChessMinimax
    src/main.cpp
    src/Board.cpp
    src/MoveGenerator.cpp
    src/Evaluator.cpp
    src/AI.cpp
    src/Game.cpp
    src/Renderer.cpp
)

target_link_libraries(ChessMinimax
    SFML::Graphics
    SFML::Window
    SFML::System
)