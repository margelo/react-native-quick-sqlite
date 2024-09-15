project(ReactNativeQuickSQLite)
cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "react-native-quick-sqlite")
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 20)
set (BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

add_definitions(
  ${SQLITE_FLAGS}
)

# Specifies a path to native header files.
include_directories(
  ../nitrogen/shared/c++
  ../nitrogen/android
  ../cpp
  ../cpp/specs
  ../cpp/sqlite
)

file(GLOB_RECURSE nitrogen_cpp_files RELATIVE ${CMAKE_SOURCE_DIR}
  "../nitrogen/shared/c++/**/*.cpp"
  "../nitrogen/android/**/*.cpp"
)

file(GLOB_RECURSE cpp_files RELATIVE ${CMAKE_SOURCE_DIR}
  "../cpp/**.c"
  "../cpp/**.cpp"
)

# Create library "RNQuickSQLite" and add all C++ files to it
add_library(
  ${PACKAGE_NAME}
  ${nitrogen_cpp_files}
  ${cpp_files}
)

set_target_properties(
  ${PACKAGE_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
)

find_library(LOG_LIB log)

target_link_libraries(
  ${PACKAGE_NAME}
  ${LOG_LIB}
  android
)
