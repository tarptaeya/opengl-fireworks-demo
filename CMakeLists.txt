cmake_minimum_required(VERSION 3.1)

project(fireworks-demo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

add_subdirectory(lib/glew-2.1.0/build/cmake)
add_subdirectory(lib/glfw-3.3.8)
add_subdirectory(lib/glm-0.9.9.8)

add_subdirectory(src)
