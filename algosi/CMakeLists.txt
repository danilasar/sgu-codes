cmake_minimum_required(VERSION 3.10)
project(algorithms LANGUAGES CXX)
include(ExternalProject)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET OFF)
add_compile_options(-Wall -Wextra -g)

# lua
find_package(Lua REQUIRED)

# sol2
FetchContent_Declare(
	sol2
	GIT_REPOSITORY https://github.com/ThePhD/sol2.git
	GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(sol2)

# toml++
FetchContent_Declare(
	tomlplusplus
	URL https://github.com/marzer/tomlplusplus/archive/refs/tags/v3.4.0.tar.gz
	URL_HASH SHA256=8517f65938a4faae9ccf8ebb36631a38c1cadfb5efa85d9a72e15b9e97d25155
	DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(tomlplusplus)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
message(STATUS "Found source files: ${SRC_FILES}")


add_executable(algorithms ${SRC_FILES})

target_include_directories(algorithms PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
	${LUA_INCLUDE_DIR}
	${sol2_SOURCE_DIR}/include
	${tomlplusplus_SOURCE_DIR}/include
)
target_link_libraries(algorithms
	tomlplusplus::tomlplusplus
	${LUA_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
