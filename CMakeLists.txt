cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

project(C2LinuxImplant VERSION 0.0.0 LANGUAGES CXX C)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --- Decide whether a prefix path was provided (var or env) ---
set(_prefixes "")

# Prefer the CMake var if set on the command line/cache.
if(DEFINED CMAKE_PREFIX_PATH AND NOT "${CMAKE_PREFIX_PATH}" STREQUAL "")
  set(_prefixes "${CMAKE_PREFIX_PATH}")
elseif(DEFINED ENV{CMAKE_PREFIX_PATH} AND NOT "$ENV{CMAKE_PREFIX_PATH}" STREQUAL "")
  # fall back to environment variable
  set(_prefixes "$ENV{CMAKE_PREFIX_PATH}")
endif()

# Optional: normalize whitespace
string(STRIP "${_prefixes}" _prefixes)

if(_prefixes)

    message(STATUS "Using CMAKE_PREFIX_PATH: ${_prefixes}")

    ##
    ## Conan Dependencies
    ##

    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

    find_package(OpenSSL REQUIRED)
    find_package(httplib REQUIRED)

    include_directories(${CMAKE_INCLUDE_PATH})


    ##
    ## C2Core dependency and build
    ##

    find_package(C2Core CONFIG REQUIRED)

    include_directories(thirdParty/base64)

    add_subdirectory(beacon/beacon)

else()

    message(STATUS "CMAKE_PREFIX_PATH not provided; using fallback strategy")

    add_definitions(-DBUILD_IMPLANT)


    ##
    ## Conan Dependencies
    ##

    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

    find_package(OpenSSL REQUIRED)
    find_package(httplib REQUIRED)

    include_directories(${CMAKE_INCLUDE_PATH})

    ##
    ## Fetch for core
    ##

    include(FetchContent)

    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
    set(BUILD_STATIC_LIBS ON CACHE BOOL "Build static libraries" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
      libssh2
      GIT_REPOSITORY https://github.com/libssh2/libssh2.git
      GIT_TAG libssh2-1.11.1
    )

    FetchContent_MakeAvailable(libssh2)


    ##
    ## Build
    ##

    include_directories(thirdParty)

    add_subdirectory(libs)

    add_subdirectory(thirdParty)
    include_directories(thirdParty/base64)
    include_directories(thirdParty/donut/include)

    set(DONUT_BUILD_DIR "${CMAKE_BINARY_DIR}/thirdParty/donut")
    add_library(Donut STATIC IMPORTED)
    set_target_properties(Donut PROPERTIES
    IMPORTED_LOCATION "${DONUT_BUILD_DIR}/lib/libdonut.a"
    )

    add_subdirectory(core/modules)
    add_subdirectory(core/beacon)

    include_directories(core/listener)
    include_directories(core/beacon)
    include_directories(core/modules/ModuleCmd)
    add_subdirectory(beacon/beacon)

endif()

