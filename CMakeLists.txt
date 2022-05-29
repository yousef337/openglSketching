cmake_minimum_required(VERSION 3.0)

project(opengl)

add_executable(${PROJECT_NAME} src/main.cpp)

install(TARGETS opengl RUNTIME DESTINATION bin)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3.7)

target_link_libraries(opengl glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(opengl OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(opengl GLEW::GLEW)
