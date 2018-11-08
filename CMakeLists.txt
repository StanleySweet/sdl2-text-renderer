##
## Author: Stanislas Daniel Claude Dolcini
## Contribs: /
##

cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME "SDL2Test")
project(${PROJECT_NAME})
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src/")

find_package(SDL2 REQUIRED)
message("Including SDL2 from: ${SDL2_INCLUDE_DIRS}" )
include_directories(${SDL2_INCLUDE_DIRS})

find_package(CAIRO REQUIRED)
message("Including Cairo from: ${CAIRO_INCLUDE_DIRS}")
include_directories(${CAIRO_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} "${SRC_DIR}/Main.cpp")
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CAIRO_LIBRARIES})

if(WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
      "${CAIRO_LIB_DIR}/cairo.dll"
      $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${SDL2_LIB_DIR}/SDL2.dll"
      $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()