cmake_minimum_required(VERSION 2.6)
project(Realio)

set (REALIO_VERSION_MAJOR 0)
set (REALIO_VERSION_MINOR 1)
set (REALIO_VERSION_PATCH 0)
set (REALIO_VERSION ${REALIO_VERSION_MAJOR}.${REALIO_VERSION_MINOR}.${REALIO_VERSION_PATCH})
set (PROJECT_VERSION "${REALIO_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Realio_SOURCE_DIR}/../CMakeModules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -pedantic-errors -ansi -Werror -Wextra -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self -std=c++11")

file(GLOB TARGET_INC ${Realio_SOURCE_DIR}/*.h)
file(GLOB TARGET_SRC
  ${Realio_SOURCE_DIR}/*.cpp
  ${Realio_SOURCE_DIR}/*.c
)

set(TARGET_SRC ${TARGET_SRC} ${TARGET_INC})

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

add_custom_target("krazy" krazy2all --priority all --export textedit --exclude license,copyright,i18ncheckarg
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library (realio SHARED ${TARGET_SRC})
target_link_libraries (realio ${Realio_libs})

add_executable (testGame test/main.cpp)
target_link_libraries (testGame realio)

install (TARGETS realio DESTINATION lib)
install (FILES ${TARGET_INC} DESTINATION include/Realio)
