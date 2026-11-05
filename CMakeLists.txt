cmake_minimum_required(VERSION 3.14)
project(VoxelEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Увімкнення вбудованого збирання залежностей SDL_mixer (вирішує проблему відсутності opusfile в хмарі)
set(SDLMIXER_VENDORED ON CACHE BOOL "" FORCE)
set(SDLMIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE)

include(FetchContent)

# Автоматичне завантаження SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

# Автоматичне завантаження SDL_mixer
FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.6.3
)
FetchContent_MakeAvailable(SDL_mixer)

# Знаходимо OpenGL
find_package(OpenGL REQUIRED)

# Збираємо всі файли коду з папки src/
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.hpp"
)

add_executable(VoxelEngine ${SOURCES})

# Підключаємо бібліотеки до нашого двигуна
target_link_libraries(VoxelEngine PRIVATE 
    SDL2::SDL2 
    SDL2_mixer::SDL2_mixer 
    OpenGL::GL
)

# Додаємо шляхи до заголовків
target_include_directories(VoxelEngine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    /usr/include
)
