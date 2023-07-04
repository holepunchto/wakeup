cmake_minimum_required(VERSION 3.25)

project(
  wakeup
  VERSION 1.0
  LANGUAGES C
)

if(APPLE)
  enable_language(OBJC)
endif()

if(NOT TARGET appling)
  add_subdirectory(vendor/libappling EXCLUDE_FROM_ALL)
endif()

add_library(wakeup OBJECT)

set_target_properties(
  wakeup
  PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

if(APPLE)
  set_target_properties(
    wakeup
    PROPERTIES
    OBJC_STANDARD 99
  )
endif()

target_sources(
  wakeup
  INTERFACE
    include/wakeup.h
  PRIVATE
    src/platform.h
    src/wakeup.c
)

if(APPLE)
  target_sources(
    wakeup
    PRIVATE
      src/darwin/launch.m
  )
endif()

target_include_directories(
  wakeup
  PUBLIC
    $<TARGET_PROPERTY:appling,INTERFACE_INCLUDE_DIRECTORIES>
)

add_subdirectory(bin)
