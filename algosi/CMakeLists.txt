cmake_minimum_required(VERSION 3.10)
project(algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDART 23)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -g)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(algorithms ${SRC_FILES})

target_include_directories(algorithms PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(lib/tomlplusplus-3.4.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
