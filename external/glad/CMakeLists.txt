cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Glad)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_DIR}/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
