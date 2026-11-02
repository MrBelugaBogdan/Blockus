cmake_minimum_required(VERSION 3.14)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)

# Автоматичне завантаження бібліотеки GLFW через CMake FetchContent
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

add_executable(VoxelEngine
    src/main.cpp
)

# Підключаємо GLFW до нашого проєкту
target_link_libraries(VoxelEngine PRIVATE glfw)

# Підключаємо OpenGL залежно від операційної системи (для Windows)
if(WIN32)
    target_link_libraries(VoxelEngine PRIVATE opengl32)
endif()
