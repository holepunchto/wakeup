add_executable(
  wakeup_bin

  $<TARGET_OBJECTS:wakeup>
  $<TARGET_OBJECTS:uv>
  $<TARGET_OBJECTS:fs>
  $<TARGET_OBJECTS:hex>
  $<TARGET_OBJECTS:path>
  $<TARGET_OBJECTS:log>
  $<TARGET_OBJECTS:appling>
  $<TARGET_OBJECTS:compact>
)

if(APPLE)
  set_target_properties(
    wakeup_bin
    PROPERTIES
    OBJC_STANDARD 99
    OUTPUT_NAME Pear
  )
endif()

if(WIN32)
  set_target_properties(
    wakeup_bin
    PROPERTIES
    OUTPUT_NAME Pear
  )
endif()

if(LINUX)
  set_target_properties(
    wakeup_bin
    PROPERTIES
    OUTPUT_NAME pear
  )
endif()

target_include_directories(
  wakeup_bin
  PRIVATE
    $<TARGET_PROPERTY:wakeup,INTERFACE_INCLUDE_DIRECTORIES>
)

if(APPLE)
  target_sources(
    wakeup_bin
    PRIVATE
      darwin/AppDelegate.h
      darwin/AppDelegate.m
      darwin/main.m
  )
endif()

if(WIN32)
  target_sources(
    wakeup_bin
    PRIVATE
      win32/main.c
  )
endif()

if(LINUX)
  target_sources(
    wakeup_bin
    PRIVATE
      linux/main.c
  )
endif()

if(APPLE)
  target_link_libraries(
    wakeup_bin
    PRIVATE
      "-framework AppKit"
  )
endif()

if(APPLE)
  add_subdirectory(darwin)
endif()

if(WIN32)
  add_subdirectory(win32)
endif()

if(LINUX)
  add_subdirectory(linux)
endif()
