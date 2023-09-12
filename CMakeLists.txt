# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(
  nosocpp
  VERSION 0.1.2
  DESCRIPTION "NosoC++ is a C++ cryptographic library that provides various cryptographic functions to work with the Noso coin."
  HOMEPAGE_URL "https://github.com/pasichDev/NosoCpp"
)

# Install rules from GNU
#include(GNUInstallDirs)

## In order to build SHARED and STATIC this needs to be changed and
## the build script needs to account for it. For the moment, practice
## building the shared version
## Have a look at:
## https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html
# Add the library source
add_library(nosocpp SHARED
  src/nCore.cpp
  src/nCripto.cpp
  src/NosoCpp.cpp
  src/nUtils.cpp
  src/WalletObject.cpp
)

# Set the lib version, public API header and Windows Export symbols
set_target_properties(nosocpp PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/NosoCpp.h
  CXX_STANDARD 20
)

## PKG Config export
configure_file(NosoCpp.pc.in nosocpp.pc @ONLY)

# Set source and include folders
target_include_directories(nosocpp PRIVATE
  include
  src
)

# Add the dependency packets
## Find required packages
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Botan
find_package(Botan REQUIRED)
target_link_libraries(nosocpp PRIVATE Botan::Botan)


# CPack configuration
## Linux
if(LINUX OR APPLE)
set_target_properties(nosocpp PROPERTIES
  SOVERSION 1
)

install(TARGETS nosocpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES
    ${CMAKE_BINARY_DIR}/nosocpp.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
install(FILES
  README.md
  LICENSE.txt
  TYPE DOC
)
endif()

## Windows
if(WINDOWS)
install(TARGETS nosocpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES
    ${CMAKE_BINARY_DIR}/nosocpp.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
install(FILES
  README.md
  LICENSE.txt
  TYPE DOC
)
endif()

include(CPack)
