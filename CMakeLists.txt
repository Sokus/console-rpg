cmake_minimum_required(VERSION 3.2)
project(console-rpg)

option(DISTRIBUTE "" OFF)

file(GLOB ENTITY_SRC ConsoleRPG/Entity/*.cpp)
file(GLOB GFXE_SRC ConsoleRPG/GFXE/*.cpp)
file(GLOB SCENE_SRC ConsoleRPG/Scene/*.cpp)
file(GLOB ANIMATOR_SRC ConsoleRPG/Animator/*.cpp)

add_executable(console-rpg
    ConsoleRPG/main.cpp
    ${ENTITY_SRC}
    ${GFXE_SRC}
    ${SCENE_SRC}
    ${ANIMATOR_SRC}
)

target_include_directories(console-rpg
    PRIVATE
        ConsoleRPG
)

if(DISTRIBUTE)
    set(RESOURCE_PATH "./Files")
else()
    set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/Files")
endif()

target_compile_definitions(console-rpg
    PRIVATE
        RESOURCE_PATH="${RESOURCE_PATH}"
)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin")
install(TARGETS console-rpg DESTINATION "${CMAKE_INSTALL_PREFIX}")
install(DIRECTORY Files DESTINATION "${CMAKE_INSTALL_PREFIX}")