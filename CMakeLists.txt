cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

project(C2LinuxImplant VERSION 0.0.0 LANGUAGES CXX C)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)


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

    ##
    ## Conan Dependencies
    ##

    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

    find_package(OpenSSL REQUIRED)
    find_package(httplib REQUIRED)

    include_directories(${CMAKE_INCLUDE_PATH})

    include_directories(thirdParty)

    ##
    ## Config Tests et Logs
    ##

    option(WITH_TESTS "Compile for tests" OFF)

    message(STATUS "WITH_TESTS is set to ${WITH_TESTS}")

    add_definitions(-DBUILD_IMPLANT)
    if(NOT WITH_TESTS)
    message(STATUS "[-] Tests are disabled.")
    else()
    message(STATUS "[+] Tests are enabled.")
    add_definitions(-DBUILD_TESTS)
    endif()


    ##
    ## Build
    ##

    add_subdirectory(libs)

    add_subdirectory(thirdParty)
    include_directories(thirdParty/base64)
    include_directories(thirdParty/donut/include)

    if(WITH_TESTS)
        enable_testing()
    endif()

    add_subdirectory(core/modules)
    add_subdirectory(core/beacon)

    include_directories(core/beacon)
    include_directories(core/modules/ModuleCmd)
    add_subdirectory(beacon/beacon)

endif()














