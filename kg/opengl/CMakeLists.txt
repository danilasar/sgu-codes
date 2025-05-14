cmake_minimum_required(VERSION 3.5)
project(ssu-graphics-opengl)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOLUTION_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

add_subdirectory(Libraries/glad)
add_subdirectory(Libraries/glfw)
add_subdirectory(Libraries/glm)
add_subdirectory(Libraries/nfd)

set(projects_dir ${CMAKE_CURRENT_LIST_DIR}/Projects)
file(GLOB children RELATIVE ${projects_dir} ${projects_dir}/*)
foreach(child ${children})
    add_subdirectory(${projects_dir}/${child})
endforeach()

