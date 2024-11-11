file(
  GENERATE
  OUTPUT Info.plist
  INPUT Info.plist
)

add_macos_iconset(
  wakeup_icon
  ICONS
    resources/icon.png 512 2x
)

add_macos_bundle(
  wakeup_bundle
  DESTINATION Pear.app
  TARGET wakeup_bin
  DEPENDS wakeup_icon
)

code_sign_macos(
  wakeup_signature
  PATH "${CMAKE_CURRENT_BINARY_DIR}/Pear.app"
  ENTITLEMENTS "Entitlements.plist"
  IDENTITY "09590CDE64938DA62FA174A68C240D346B05EF49"
  DEPENDS wakeup_bundle
)
