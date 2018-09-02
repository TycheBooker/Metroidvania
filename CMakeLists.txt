# CMakeList.txt : CMake project for Metroidvania, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Metroidvania)

#set the C++ standard to be used
set (CMAKE_CXX_STANDARD 11)

# Bring the headers into the project
include_directories(include include/States include/General)

## set source files
# set (SOURCES 
#		main.cpp 
#		Game.cpp 
#		Window.cpp 
#		EventManager.cpp)
file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")

## If you want to link SFML statically
if (NOT APPLE)
  set(SFML_STATIC_LIBRARIES TRUE)
endif(NOT APPLE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

# Add source to this project's executable.
add_executable (Metroidvania ${SOURCES})

# Copy Data files to build location
file(COPY "data/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(Metroidvania sfml-graphics sfml-audio sfml-system sfml-window)

# TODO: Add tests and install targets if needed.
