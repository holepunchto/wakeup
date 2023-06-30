file(
  GENERATE
  OUTPUT Info.plist
  INPUT Info.plist
  TARGET wakeup_bin
)

install(
  TARGETS wakeup_bin
  RUNTIME DESTINATION Wakeup.app/Contents/MacOS
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
  DESTINATION Wakeup.app/Contents
)

install(
  FILES resources/icon.icns
  DESTINATION Wakeup.app/Contents/Resources
)
