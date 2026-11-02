cmake_minimum_required(VERSION 3.14)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Завантажуємо SDL2 для вікон і подій
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

# Завантажуємо GLM (математична бібліотека для 3D у C++)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

add_executable(VoxelEngine src/main.cpp)

target_link_libraries(VoxelEngine PRIVATE SDL2::SDL2 glm::glm)

if(WIN32)
    target_link_libraries(VoxelEngine PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(VoxelEngine PRIVATE "-framework OpenGL")
endif()
