cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

project(C2LinuxImplant VERSION 0.0.0 LANGUAGES CXX C)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(C2CORE_BUILD_TESTS "Enable C2Core tests from the parent project" OFF)
if(C2CORE_BUILD_TESTS)
  enable_testing()
endif()

set(C2_RUNTIME_MODULE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Release/Modules" CACHE PATH
    "Directory where C2Core runtime modules are copied after build")
set(C2_TEST_BIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/tests" CACHE PATH
    "Directory where C2Core test binaries are copied after build")

file(MAKE_DIRECTORY "${C2_RUNTIME_MODULE_OUTPUT_DIR}")
file(MAKE_DIRECTORY "${C2_TEST_BIN_OUTPUT_DIR}")


add_definitions(-DBUILD_IMPLANT)


##
## Conan Dependencies
##

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(OpenSSL REQUIRED)
find_package(httplib REQUIRED)
find_package(Libssh2 REQUIRED)
find_package(nlohmann_json REQUIRED CONFIG)
if(C2CORE_BUILD_TESTS)
  find_package(Catch2 REQUIRED CONFIG)
endif()

include_directories(${CMAKE_INCLUDE_PATH})

get_target_property(C2_NLOHMANN_JSON_INCLUDE_DIRS nlohmann_json::nlohmann_json INTERFACE_INCLUDE_DIRECTORIES)
if(C2_NLOHMANN_JSON_INCLUDE_DIRS)
  include_directories(BEFORE ${C2_NLOHMANN_JSON_INCLUDE_DIRS})
endif()


##
## Build
##

include_directories(thirdParty)

add_subdirectory(libs)
if(C2CORE_BUILD_TESTS)
  add_test(NAME dnsTest COMMAND dnsTest)
  add_test(NAME utilsTest COMMAND utilsTest)
  # fonctionalTest is a manual server/client harness that requires runtime args.
  # Keep it built, but do not register it in CI ctest without explicit parameters.
  add_test(NAME responseDecodeTest COMMAND responseDecodeTest)
  add_test(NAME messageTest COMMAND messageTest)
  add_test(NAME interleavedTest COMMAND interleavedTest)
  add_test(NAME TestsSockerHandler COMMAND TestsSockerHandler)
  add_test(NAME TestsSocksServer COMMAND TestsSocksServer)
endif()

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
if(C2CORE_BUILD_TESTS)
  add_subdirectory(core/beacon/tests)
  add_subdirectory(core/listener/tests)
endif()

include_directories(core/listener)
include_directories(core/beacon)
include_directories(core/modules/ModuleCmd)
add_subdirectory(beacon/beacon)


