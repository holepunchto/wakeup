install(
  TARGETS wakeup_bin
  RUNTIME DESTINATION Wakeup.app/Contents/MacOS
)

install(
  FILES Info.plist
  DESTINATION Wakeup.app/Contents
)

install(
  FILES resources/icon.icns
  DESTINATION Wakeup.app/Contents/Resources
)
