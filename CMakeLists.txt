cmake_minimum_required(VERSION 3.21)
project(Software3DRender CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.0
    GIT_SHALLOW TRUE
)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)

set(SWR_DIR ${CMAKE_SOURCE_DIR}/Software3DRenderer/SWR)

add_library(swr STATIC
    ${SWR_DIR}/Bitmap.cpp
    ${SWR_DIR}/RenderContext.cpp
    ${SWR_DIR}/Display.cpp
    ${SWR_DIR}/DisplayFactory.cpp
    ${SWR_DIR}/Scene.cpp
    ${SWR_DIR}/Vertex.cpp
    ${SWR_DIR}/Scenes/Star3DFieldScene.cpp
    ${SWR_DIR}/Scenes/FillShapeScene.cpp
    ${SWR_DIR}/Scenes/TrianglesScene.cpp
)
target_include_directories(swr PUBLIC
    ${SWR_DIR}
    ${SWR_DIR}/Scenes
)

add_executable(Software3DRenderer WIN32 app/main.cpp)
target_link_libraries(Software3DRenderer PRIVATE swr SDL3::SDL3-static)

enable_testing()

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(swr_tests tests/swr_tests.cpp)
target_link_libraries(swr_tests PRIVATE swr Catch2::Catch2WithMain)
add_test(NAME swr_tests COMMAND swr_tests)
