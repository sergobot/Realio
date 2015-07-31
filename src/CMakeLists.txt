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

configure_file(test/image1.png image1.png COPYONLY)
configure_file(test/image2.png image2.png COPYONLY)

add_library (realio SHARED ${TARGET_SRC})
target_link_libraries (realio ${Realio_libs})

add_executable (testGame test/main.cpp)
target_link_libraries (testGame realio)

install (TARGETS realio DESTINATION lib)
install (FILES ${TARGET_INC} DESTINATION include/realio)
