#!/usr/bin/env powershell

$GENERATE_PRESET       = "ninja-multi-vcpkg"
$BUILD_PRESET          = "ninja-vcpkg-release"
$TEST_PRESET           = "test-release"
$PACKAGE_PRESET_ZIP    = "package-zip-release"
#$PACKAGE_PRESET_TGZ    = "package-tar-gz-release"
#$PACKAGE_PRESET_DEB    = "package-deb-release"
#$PACKAGE_PRESET_RPM    = "package-rpm-release"
$PACKAGE_PRESET_NSIS64 = "package-nsis64-release"

$WORKFLOW_PRESET       ="workflow-ninja-vcpkg-windows"


if ( $WORKFLOW_PRESET ) {
  echo "#####"
  echo "# Calling CMake workflow: $WORKFLOW_PRESET"
  echo "#####"
  cmake --workflow --preset "$WORKFLOW_PRESET"
  exit
}

if ( $GENERATE_PRESET ) {
  echo "#####"
  echo "# Creating CMake build files"
  echo "#####"
  cmake --preset $GENERATE_PRESET
}

if ( !$? ) {
  exit
} elseif ( $BUILD_PRESET ) {
  echo ""
  echo "#####"
  echo "# Building TestNosoCPP"
  echo "#####"
  cmake --build --preset $BUILD_PRESET
}

if ( !$? ) {
  exit
} elseif ( $PACKAGE_PRESET_ZIP ) {
  echo ""
  echo "#####"
  echo "# Packaging NosoCpp *.zip"
  echo "#####"
  cpack --preset $PACKAGE_PRESET_ZIP
}

if ( !$? ) {
  exit
} elseif ( $PACKAGE_PRESET_TGZ ) {
  echo ""
  echo "#####"
  echo "# Packaging NosoCpp *.tar.gz"
  echo "#####"
  cpack --preset $PACKAGE_PRESET_TGZ
}

if ( !$? ) {
  exit
} elseif ( $PACKAGE_PRESET_DEB ) {
  echo ""
  echo "#####"
  echo "# Packaging NosoCpp *.deb"
  echo "#####"
  cpack --preset $PACKAGE_PRESET_DEB
}

if ( !$? ) {
  exit
} elseif ( $PACKAGE_PRESET_RPM ) {
  echo ""
  echo "#####"
  echo "# Packaging NosoCpp *.rpm"
  echo "#####"
  cpack --preset $PACKAGE_PRESET_RPM
}

if ( !$? ) {
  exit
} elseif ( $PACKAGE_PRESET_NSIS64 ) {
  echo ""
  echo "#####"
  echo "# Packaging NosoCpp install.exe"
  echo "#####"
  cpack --preset $PACKAGE_PRESET_NSIS64
}
