cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

project(C2LinuxImplant VERSION 0.0.0 LANGUAGES CXX C)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 23)

##
## Conan Dependencies
##

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(Boost REQUIRED)  
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

if(WITH_TESTS)
    add_subdirectory(core/beacon/tests)
    add_subdirectory(core/listener/tests)
endif()


