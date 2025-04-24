cmake_minimum_required(VERSION 3.10)
project(algorithms LANGUAGES CXX)
include(ExternalProject)

set(CMAKE_CXX_STANDART 23)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -g)

# lua
set(LUA_VERSION "lua-5.4.7")
ExternalProject_Add(lua_project
  PREFIX ${CMAKE_BINARY_DIR}/${LUA_VERSION}
  URL https://www.lua.org/ftp/${LUA_VERSION}.tar.gz
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make generic
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE true
  DOWNLOAD_EXTRACT_TIMESTAMP false
)
ExternalProject_Get_Property(lua_project BINARY_DIR)
set(LUA_INCLUDE_DIR ${BINARY_DIR}/src)
set(LUA_LIBRARIES ${BINARY_DIR}/src/liblua.a)
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# toml++
include(FetchContent)
FetchContent_Declare(
	tomlplusplus
	URL https://github.com/marzer/tomlplusplus/archive/refs/tags/v3.4.0.tar.gz
	URL_HASH SHA256=8517f65938a4faae9ccf8ebb36631a38c1cadfb5efa85d9a72e15b9e97d25155
	DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(tomlplusplus)

add_executable(algorithms ${SRC_FILES})

target_include_directories(algorithms PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(algorithms tomlplusplus::tomlplusplus)


add_dependencies(algorithms lua_project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
