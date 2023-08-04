file(
  GENERATE
  OUTPUT main.rc
  INPUT main.rc
)

file(
  COPY resources/icon.ico
  DESTINATION resources
)

target_link_options(
  wakeup_bin
  PRIVATE
    /subsystem:windows
    /entry:mainCRTStartup
)

target_sources(
  wakeup_bin
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/main.rc
)

install(
  TARGETS wakeup_bin
  RUNTIME DESTINATION Pear
)
