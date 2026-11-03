cmake_minimum_required(VERSION 3.14)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Завантажуємо SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

# Завантажуємо SDL2_mixer для звуків
FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.6.3
)
set(SDLMIXER_OPUS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL_mixer)

# Завантажуємо GLM для 3D математики
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

add_executable(VoxelEngine src/main.cpp)

target_link_libraries(VoxelEngine PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer glm::glm)

if(WIN32)
    target_link_libraries(VoxelEngine PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(VoxelEngine PRIVATE "-framework OpenGL")
endif()
