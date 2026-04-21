set(C2_BASE64_SOURCE_DIR "${CMAKE_SOURCE_DIR}/thirdParty/base64" CACHE PATH
    "Path to the cpp-base64 source tree consumed by C2Core")
set(C2_DONUT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/thirdParty/donut" CACHE PATH
    "Path to the donut source tree consumed by C2Core")

add_library(c2_base64 STATIC
  "${C2_BASE64_SOURCE_DIR}/base64.cpp"
)

target_include_directories(c2_base64 PUBLIC
  "${C2_BASE64_SOURCE_DIR}"
)

set_target_properties(c2_base64 PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

# donut
file(COPY "${C2_DONUT_SOURCE_DIR}" DESTINATION "${CMAKE_BINARY_DIR}/thirdParty")
execute_process(COMMAND bash -c "cd ${CMAKE_BINARY_DIR}/thirdParty/donut && make -f Makefile")
set(Donut "${CMAKE_BINARY_DIR}/thirdParty/donut/lib/libdonut.a" PARENT_SCOPE)
set(aplib64 "${CMAKE_BINARY_DIR}/thirdParty/donut/lib/aplib64.a" PARENT_SCOPE)
