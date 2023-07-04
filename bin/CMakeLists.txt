add_executable(wakeup_bin  $<TARGET_OBJECTS:wakeup>)

set_target_properties(
  wakeup_bin
  PROPERTIES
  VERSION ${PROJECT_VERSION}
)

if(APPLE)
  set_target_properties(
    wakeup_bin
    PROPERTIES
    OBJC_STANDARD 99
    OUTPUT_NAME Wakeup
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

target_link_libraries(
  wakeup_bin
  PRIVATE
    appling_static
)

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
