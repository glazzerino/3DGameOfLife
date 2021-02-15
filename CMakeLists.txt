cmake_minimum_required(VERSION 3.5)
project(gameoflife)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME gameoflife)

LINK_DIRECTORIES(${src/})
link_libraries(raylib GL m pthread dl)
add_executable(gameoflife src/main.cpp)
