cmake_minimum_required(VERSION 3.25)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-macos REQUIRED PATHS node_modules/cmake-macos)
find_package(cmake-windows REQUIRED PATHS node_modules/cmake-windows)

project(
  wakeup
  VERSION 1.2
  LANGUAGES C
)

if(APPLE)
  enable_language(OBJC)
endif()

if(MSVC)
  add_compile_options(/MT$<$<CONFIG:Debug>:d>)
endif()

fetch_package("github:holepunchto/libappling")

add_library(wakeup OBJECT)

set_target_properties(
  wakeup
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  wakeup
  INTERFACE
    include/wakeup.h
  PRIVATE
    src/wakeup.c
)

target_include_directories(
  wakeup
  PUBLIC
    $<TARGET_PROPERTY:appling,INTERFACE_INCLUDE_DIRECTORIES>
  PRIVATE
    $<TARGET_PROPERTY:path,INTERFACE_INCLUDE_DIRECTORIES>
)

add_subdirectory(bin)
