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
    $<$<CONFIG:Release>:/subsystem:windows /entry:mainCRTStartup>
)

target_sources(
  wakeup_bin
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/main.rc
)

code_sign_windows(
  wakeup_signature
  TARGET wakeup_bin
  THUMBPRINT "E890AF027C9C83F7427BCEEBE7AC533579DFE549"
)
