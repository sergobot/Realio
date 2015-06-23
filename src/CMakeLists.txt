cmake_minimum_required(VERSION 2.6)
project(Realio)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Realio_SOURCE_DIR}/../CMakeModules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB TARGET_INC ${Realio_SOURCE_DIR}/*.h)
file(GLOB TARGET_SRC
  ${Realio_SOURCE_DIR}/*.cpp
  ${Realio_SOURCE_DIR}/*.c
)

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_INC})

find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

set(Realio_libs
  ${OPENGL_LIBRARY}
  ${ASSIMP_LIBRARY}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARY}
)

include_directories(${SDL2_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

add_library (Realio SHARED ${TARGET_SRC})
target_link_libraries (Realio ${Realio_libs})

install (TARGETS Realio DESTINATION lib)
install (FILES ${TARGET_INC} DESTINATION include/Realio)
