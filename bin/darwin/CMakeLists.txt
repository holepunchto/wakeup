file(
  GENERATE
  OUTPUT Info.plist
  INPUT Info.plist
)

install(
  TARGETS wakeup_bin
  RUNTIME DESTINATION Pear.app/Contents/MacOS
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
  DESTINATION Pear.app/Contents
)

install(
  FILES resources/icon.icns
  DESTINATION Pear.app/Contents/Resources
)
