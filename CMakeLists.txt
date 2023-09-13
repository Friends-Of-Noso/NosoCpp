# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(
  NosoCpp
  VERSION 0.1.0
  DESCRIPTION "NosoC++ is a C++ cryptographic library that provides various cryptographic functions to work with the Noso coin."
  HOMEPAGE_URL "https://github.com/pasichDev/NosoCpp"
)

# Install rules from GNU
include(GNUInstallDirs)

## In order to build SHARED and STATIC this needs to be changed and
## the build script needs to account for it. For the moment, practice
## building the shared version
## Have a look at:
## https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html
# Add the library source
add_library(NosoCpp SHARED
  src/nCore.cpp
  src/nCripto.cpp
  src/NosoCpp.cpp
  src/nUtils.cpp
  src/WalletObject.cpp
)

# Set the lib version, public API header and Windows Export symbols
set_target_properties(NosoCpp PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/NosoCpp.h
  OUTPUT_NAME nosocpp
  CXX_STANDARD 20
)

## PKG Config export
configure_file(NosoCpp.pc.in nosocpp.pc @ONLY)

# Set source and include folders
target_include_directories(NosoCpp PRIVATE
  include
  src
)

# Add the dependency packets
## Find required packages
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Botan
find_package(Botan REQUIRED)
target_link_libraries(NosoCpp PRIVATE Botan::Botan)

# CPack configuration
## Linux
if(LINUX OR APPLE)

message(STATUS
  "Configuring CPack for Linux or Apple"
)

set_target_properties(NosoCpp PROPERTIES
  SOVERSION 1
)

install(TARGETS NosoCpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES
    ${CMAKE_BINARY_DIR}/nosocpp.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
endif()

## Windows
if(WINDOWS)

message(STATUS
  "Configuring CPack for Windows"
)

install(TARGETS NosoCpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES
    ${CMAKE_BINARY_DIR}/nosocpp.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
endif()

install(FILES
  include/Constants.h
  include/nCore.h
  include/nCripto.h
  include/nUtils.h
  include/Objects.h
  include/WalletObject.h
  DESTINATION include
)

install(FILES
  README.md
  LICENSE.txt
  TYPE DOC
)

include(CPack)
