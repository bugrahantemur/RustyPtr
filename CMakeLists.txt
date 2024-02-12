cmake_minimum_required(VERSION 3.27)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

project(
  "Rusty Pointers"
  VERSION 0.1.0
  DESCRIPTION
    "A header only c++ library that provides Rust like pointers in C++"
  HOMEPAGE_URL "https://github.com/bugrahantemur/RustyPtr"
  LANGUAGES CXX)

include(GNUInstallDirs)

option(RUSTYPTR_INSTALL_LIBRARY
       "Enable installing of Rusty Pointers library into default locations"
       ${PROJECT_IS_TOP_LEVEL})
option(RUSTYPTR_BUILD_TESTING "Build and run tests" ${PROJECT_IS_TOP_LEVEL})

if(RUSTYPTR_BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/b10fad38c4026a29ea6561ab15fc4818170d1c10.zip
  )
  FetchContent_MakeAvailable(googletest)
endif()

add_library(RustyPtr INTERFACE)
add_library(RustyPtr::RustyPtr ALIAS RustyPtr)

target_include_directories(
  RustyPtr INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(RustyPtr INTERFACE cxx_std_11)

if(RUSTYPTR_BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

if(RUSTYPTR_INSTALL_LIBRARY)
  install(
    TARGETS RustyPtr
    EXPORT RustyPtrTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    "RustyPtrConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

  configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/RustyPtrConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/RustyPtrConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/RustyPtr/cmake)

  install(
    EXPORT RustyPtrTargets
    FILE RustyPtrTargets.cmake
    NAMESPACE RustyPtr::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/RustyPtr/cmake)

  install(FILES "${PROJECT_BINARY_DIR}/RustyPtrConfig.cmake"
                "${PROJECT_BINARY_DIR}/RustyPtrConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/RustyPtr/cmake)

  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/RustyPtr
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
include(CPack)