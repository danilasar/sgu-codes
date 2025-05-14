cmake_minimum_required(VERSION 3.5)
project(glad LANGUAGES C)
add_library (glad src/glad.c)
target_include_directories (glad PUBLIC ${PROJECT_SOURCE_DIR}/include)
