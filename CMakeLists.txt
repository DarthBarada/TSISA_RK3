# CMakeList.txt : CMake project for TSISA_LAB04, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(lab04)

set(SOURCES ${PROJECT_NAME}Sources)

add_library(
${SOURCES}
STATIC
${CMAKE_CURRENT_SOURCE_DIR}/GeneticAlg.cpp
)

target_link_directories(
${SOURCES}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/GeneticAlg.h
)

# Add source to this project's executable.
add_executable (main "main.cpp")

#target_link_directories(
#main
#PUBLIC
#${CMAKE_CURRENT_SOURCE_DIR}/GeneticAlg.h
#)

target_link_libraries(main ${SOURCES})