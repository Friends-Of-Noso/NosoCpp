#!/bin/bash

GENERATE_PRESET=ninja-multi-vcpkg
BUILD_PRESET=ninja-vcpkg-release
#PACKAGE_PRESET_ZIP=package-zip-release
#PACKAGE_PRESET_TGZ=package-tar-gz-release
PACKAGE_PRESET_DEB=package-deb-release
#PACKAGE_PRESET_RPM=package-rpm-release
#PACKAGE_PRESET_NSIS64=package-nsis64-release
BUILDS=builds/ninja-multi-vcpkg

if [ "$1" == "--clean" ]
then
  echo "#####"
  echo "# Cleaning builds folder"
  echo "#####"
  if [ -d ${BUILDS} ]
  then
    rm -r ${BUILDS}
  else
    echo
    echo "Nothing to clean"
  fi
fi

echo "#####"
echo "# Creating CMake build files"
echo "#####"
cmake --preset ${GENERATE_PRESET}

if [ $? == 0 ]
then
  echo
  echo "#####"
  echo "# Building NosoCpp"
  echo "#####"
  cmake --build --preset ${BUILD_PRESET}
fi

if [ $? == 0 ] && [ "${PACKAGE_PRESET_ZIP}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.zip"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_ZIP}
fi

if [ $? == 0 ] && [ "${PACKAGE_PRESET_TGZ}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.tar.gz"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_TGZ}
fi

if [ $? == 0 ] && [ "${PACKAGE_PRESET_DEB}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.deb"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_DEB}
fi

if [ $? == 0 ] && [ "${PACKAGE_PRESET_RPM}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.rpm"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_RPM}
fi

if [ $? == 0 ] && [ "${PACKAGE_PRESET_NSIS64}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp install.exe"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_NSIS64}
fi
