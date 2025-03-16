cmake_minimum_required(VERSION 3.31.6)
project(HttpServer C)

include_directories(${CMAKE_SOURCE_DIR}/Includes)

file(GLOB SOURCES Srcs/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
