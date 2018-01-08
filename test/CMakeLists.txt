if(NOT EXISTS "${CMAKE_BINARY_DIR}/test/catch.hpp")
  message(STATUS "Downloading catch.hpp from https://github.com/CatchOrg/Catch")
  file(DOWNLOAD "https://raw.githubusercontent.com/CatchOrg/Catch2/master/single_include/catch.hpp"
                "${CMAKE_BINARY_DIR}/test/catch.hpp")
endif()

set(TEST_SOURCES PrimeNumberGeneratorTest.cpp)

include_directories(${CMAKE_BINARY_DIR}/test)
add_executable(primeTest ${TEST_SOURCES} ${CMAKE_BINARY_DIR}/test/catch.hpp)
target_link_libraries(primeTest Red)
set_target_properties(primeTest PROPERTIES CXX_STANDARD 17)

add_test(PrimeTest primeTest)
