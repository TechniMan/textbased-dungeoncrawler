cmake_minimum_required(VERSION 3.15.5)
set (CMAKE_CXX_STANDARD 17)
project(textbased_dungeoncrawler)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

add_executable(textbased_dungeoncrawler ${SOURCES})
