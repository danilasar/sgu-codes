get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C CXX)

file(GLOB_RECURSE HEADERS "*.hpp" "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE glad)
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE glm)
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE nfd)

if(WIN32)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${SOLUTION_ROOT})
endif()

if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
    
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} LINK_PRIVATE X11)
    target_link_libraries(${PROJECT_NAME} LINK_PRIVATE ${GTK3_LIBRARIES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

