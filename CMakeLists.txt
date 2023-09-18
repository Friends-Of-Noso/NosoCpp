# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(
  NosoCpp
  VERSION 0.2.7
  DESCRIPTION "NosoC++ is a C++ cryptographic library that provides various cryptographic functions to work with the Noso coin."
  HOMEPAGE_URL "https://github.com/pasichDev/NosoCpp"
)


## Tests
enable_testing()
## Tests
add_subdirectory(tests)


# Source Files
set(NOSO_SOURCE_FILES
    src/NosoAddress.cpp
    src/NosoCore.cpp
    src/NosoUtils.cpp
    src/VerifySing.cpp
)

# Header Files
set(NOSO_INSTALL_HEADER_FILES
  include/Constants.h
  include/NosoAddress.h
  include/NosoCore.h
  include/NosoUtils.h
  include/Objects.h
  include/VerifySing.h
  include/WalletObject.h
)

# Shared Exports
set(NOSOCPP_SHARED_BASE_NAME "shared")
set(NOSOCPP_SHARED_EXPORTS "shared_exports")

string(TOLOWER ${PROJECT_NAME} NOSOCPP_LIB_NAME)

# Add the library source SHARED
if (NOSOCPP_MAKE_SHARED)
  add_library(NosoCpp SHARED
    ${NOSO_SOURCE_FILES}
  )

  include (GenerateExportHeader)

  # generates the export header shared_exports.h automatically
  GENERATE_EXPORT_HEADER(NosoCpp
      BASE_NAME ${NOSOCPP_SHARED_BASE_NAME}
      EXPORT_MACRO_NAME ${NOSOCPP_SHARED_EXPORTS}
      EXPORT_FILE_NAME ${NOSOCPP_SHARED_EXPORTS}.h
      STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
  )

  install(FILES
    ${CMAKE_BINARY_DIR}/${NOSOCPP_SHARED_EXPORTS}.h
    DESTINATION include
  )
  if (MSVC)
    set(
      CPACK_PACKAGE_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}${NOSOCPP_LIB_NAME}-shared"
    )
  else()
    set(
      CPACK_PACKAGE_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}${NOSOCPP_LIB_NAME}"
    )
  endif()
endif()
# Add the library source SHARED

# Add the library source STATIC
if (NOSOCPP_MAKE_STATIC)
  add_library(NosoCpp STATIC
    ${NOSO_SOURCE_FILES}
  )
  if (MSVC)
    set(
      CPACK_PACKAGE_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}${NOSOCPP_LIB_NAME}-static"
    )
  else()
    set(
      CPACK_PACKAGE_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}${NOSOCPP_LIB_NAME}-dev"
    )
  endif()
endif()
# Add the library source STATIC

# Set the lib version, public API header
set_target_properties(NosoCpp PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/${PROJECT_NAME}.h
  OUTPUT_NAME ${NOSOCPP_LIB_NAME}
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

# OS and CPack configuration
## Linux or Apple
if(LINUX OR APPLE)

  message(
    "Configuring CPack for Linux or Apple"
  )

  # Install rules from GNU
  include(GNUInstallDirs)
  # Lower case on these
  set( DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${NOSOCPP_LIB_NAME} )
  set( CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${NOSOCPP_LIB_NAME} )

  set_target_properties(NosoCpp PROPERTIES
    SOVERSION 1
  )

  install(TARGETS NosoCpp
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
  install(FILES
      ${CMAKE_BINARY_DIR}/${NOSOCPP_LIB_NAME}.pc
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
  )
endif()
## Linux or Apple

## Windows
if(MSVC)

  message(
    "Configuring CPack for Windows"
  )

  install(TARGETS NosoCpp
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


  install(FILES
      ${CMAKE_BINARY_DIR}/${NOSOCPP_LIB_NAME}.pc
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
  )

  include(InstallRequiredSystemLibraries)

endif()
## Windows

install(FILES
  ${NOSO_INSTALL_HEADER_FILES}
  DESTINATION include
)

install(FILES
  README.md
  LICENSE.txt
  TYPE DOC
)

include(CPack)
