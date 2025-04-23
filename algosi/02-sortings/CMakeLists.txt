cmake_minimum_required(VERSION 3.10)
project(sortings LANGUAGES CXX)

set(CMAKE_CXX_STANDART 23)
set(CMAKE_CXX_STANDART_REQUIRED ON)
add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(sortings ${SRC_FILES})

target_include_directories(sortings PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
