cmake_minimum_required(VERSION 3.9)
project("Rendering Engine Project")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(bump main.cpp application.hpp camera.cpp shader.cpp program.cpp mesh.hpp mesh.cpp model.hpp model.cpp renderer.hpp renderer.cpp texture.hpp texture.cpp material.hpp path.hpp path.cpp)

target_link_libraries(bump ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})