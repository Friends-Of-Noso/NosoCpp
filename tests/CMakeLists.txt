# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(
  TestingNosoCpp
)

# Tests
set(testDriver "TestNosoCpp")

## create the testing file and list of tests
create_test_sourcelist (Tests
  ${testDriver}.cpp
  TestGenAddress.cpp
  TestImportAddressForKeys.cpp
)

## add the executable
add_executable (${testDriver} ${Tests})

target_include_directories(${testDriver} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

## remove the test driver source file
set (TestsToRun ${Tests})
remove (TestsToRun ${testDriver}.cpp)

## Add all the ADD_TEST for each test
foreach (test ${TestsToRun})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND ${testDriver} ${TName})
endforeach ()

# NosoCpp
target_link_libraries(${testDriver} PRIVATE
  NosoCpp
)

# Botan
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(Botan REQUIRED)
target_link_libraries(${testDriver} PRIVATE
  Botan::Botan
)
