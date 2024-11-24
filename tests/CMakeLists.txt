cmake_minimum_required(VERSION 3.14)
project(neocalc_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Catch2 3 REQUIRED)

set(NEOMATH_TEST
  neomath/neomath_test.cpp
)

include_directories(../../include/neomath/external)

add_executable(tests
  ${NEOMATH_TEST}
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ../../include)
