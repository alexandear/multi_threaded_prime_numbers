cmake_minimum_required(VERSION 3.2)

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if (ENABLE_COVERAGE)
  add_compile_options(--coverage -O0)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(Red src/PrimeNumberGenerator.cpp)
set_target_properties(Red PROPERTIES CXX_STANDARD 17)
target_include_directories (Red PUBLIC src)
if (ENABLE_COVERAGE)
  target_link_libraries(Red --coverage)
endif()

add_executable(prime src/main.cpp)
set_target_properties(prime PROPERTIES CXX_STANDARD 17)
target_link_libraries (prime LINK_PUBLIC Red)


if(NOT EXISTS "${CMAKE_BINARY_DIR}/include/catch.hpp")
  message(STATUS "Downloading catch.hpp from https://github.com/CatchOrg/Catch")
  file(DOWNLOAD "https://raw.githubusercontent.com/CatchOrg/Catch2/master/single_include/catch.hpp"
                "${CMAKE_BINARY_DIR}/include/catch.hpp")
endif()

enable_testing()

set(TEST_SOURCES test/PrimeNumberGeneratorTest.cpp)

include_directories(${CMAKE_BINARY_DIR}/include)
add_executable(primeTest ${TEST_SOURCES} ${CMAKE_BINARY_DIR}/include/catch.hpp)
target_link_libraries(primeTest Red)
set_target_properties(primeTest PROPERTIES CXX_STANDARD 17)

add_test(PrimeTest primeTest)
