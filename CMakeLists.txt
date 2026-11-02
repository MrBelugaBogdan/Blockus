cmake_minimum_required(VERSION 3.14)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)

# Автоматичне завантаження бібліотеки SDL2 через CMake FetchContent (для ПК/Mac)
if(NOT ANDROID AND NOT IOS)
    include(FetchContent)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.5
    )
    FetchContent_MakeAvailable(SDL2)
endif()

add_executable(VoxelEngine
    src/main.cpp
)

# Підключаємо SDL2 залежно від платформи
if(ANDROID)
    find_package(SDL2 REQUIRED)
    target_link_libraries(VoxelEngine PRIVATE SDL2::SDL2 GLESv2 log)
elseif(IOS)
    find_package(SDL2 REQUIRED)
    target_link_libraries(VoxelEngine PRIVATE SDL2::SDL2)
else()
    target_link_libraries(VoxelEngine PRIVATE SDL2::SDL2)
    if(WIN32)
        target_link_libraries(VoxelEngine PRIVATE opengl32)
    elseif(APPLE)
        target_link_libraries(VoxelEngine PRIVATE "-framework OpenGL")
    endif()
endif()
