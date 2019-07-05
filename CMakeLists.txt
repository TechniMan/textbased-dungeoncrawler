cmake_minimum_required(VERSION 3.5.1)
set (CMAKE_CXX_STANDARD 11)
project(textbased_dungeoncrawler)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(textbased_dungeoncrawler ${SOURCES})
