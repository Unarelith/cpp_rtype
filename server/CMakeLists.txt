#------------------------------------------------------------------------------
# CMakeLists.txt
# for ModularGameEngine
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)

project(rtype)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#------------------------------------------------------------------------------
# Get source files
#------------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES source/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp ../game/*.hpp)

foreach(HEADER_FILE ${HEADER_FILES})
	get_filename_component(HEADER_DIRECTORY ${HEADER_FILE} DIRECTORY)
	include_directories(${HEADER_DIRECTORY})
endforeach(HEADER_FILE)

#------------------------------------------------------------------------------
# Add executables
#------------------------------------------------------------------------------
add_executable(${CMAKE_PROJECT_NAME}_server ${SOURCE_FILES})
add_dependencies(${CMAKE_PROJECT_NAME}_server ${CMAKE_PROJECT_NAME}_game)

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfatal-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_ENABLED")

#------------------------------------------------------------------------------
# Link options
#------------------------------------------------------------------------------
target_link_libraries(${CMAKE_PROJECT_NAME}_server
                      ${OPENGL_LIBRARIES}
                      ${SDL2_LIBRARIES}
                      ${SDL2IMAGE_LIBRARIES}
                      ${SDL2MIXER_LIBRARIES}
                      ${SDL2TTF_LIBRARIES}
                      ${TINYXML2_LIBRARIES}
                      ${GAMEKIT_LIBRARIES}
                      sfml-network
                      ${CMAKE_PROJECT_NAME}_game)

