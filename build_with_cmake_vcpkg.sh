#!/bin/bash

LINK_OPTION="-shared"
GENERATE_PRESET="ninja-multi-vcpkg${LINK_OPTION}"
BUILD_PRESET="ninja-vcpkg-release${LINK_OPTION}"
PACKAGE_PRESET_ZIP="package-zip-release${LINK_OPTION}"
PACKAGE_PRESET_TGZ="package-tar-gz-release${LINK_OPTION}"
PACKAGE_PRESET_DEB="package-deb-release${LINK_OPTION}"
PACKAGE_PRESET_RPM="package-rpm-release${LINK_OPTION}"
#PACKAGE_PRESET_NSIS64="package-nsis64-release${LINK_OPTION}"

BUILDS="builds"

#WORKFLOW_PRESET="workflow-ninja-vcpkg-linux"

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

if [ "${WORKFLOW_PRESET}" != "" ]
then
  echo "#####"
  echo "# Calling CMake workflow: ${WORKFLOW_PRESET}"
  echo "#####"
  cmake --workflow --preset "${WORKFLOW_PRESET}"
  exit
fi

echo "#####"
echo "# Creating CMake build files"
echo "#####"
cmake --preset ${GENERATE_PRESET}

if [ $? != "0" ]
then
  exit
elif [ "${BUILD_PRESET}" != "" ]
then
  echo
  echo "#####"
  echo "# Building NosoCpp"
  echo "#####"
  cmake --build --preset ${BUILD_PRESET}
fi

if [ $? != "0" ]
then
  exit
elif [ "${PACKAGE_PRESET_ZIP}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.zip"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_ZIP}
fi

if [ $? != "0" ]
then
  exit
elif [ "${PACKAGE_PRESET_TGZ}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.tar.gz"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_TGZ}
fi

if [ $? != "0" ]
then
  exit
elif [ "${PACKAGE_PRESET_DEB}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.deb"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_DEB}
fi

if [ $? != "0" ]
then
  exit
elif [ "${PACKAGE_PRESET_RPM}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp *.rpm"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_RPM}
fi

if [ $? != "0" ]
then
  exit
elif [ "${PACKAGE_PRESET_NSIS64}" != "" ]
then
  echo
  echo "#####"
  echo "# Packaging NosoCpp install.exe"
  echo "#####"
  cpack --preset ${PACKAGE_PRESET_NSIS64}
fi
