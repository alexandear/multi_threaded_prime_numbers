project(primeTest)

set(CATCH_HPP "${CMAKE_BINARY_DIR}/test/catch.hpp")

if(NOT EXISTS ${CATCH_HPP})
  message(STATUS "Downloading catch.hpp from https://github.com/CatchOrg/Catch")
  file(DOWNLOAD "https://raw.githubusercontent.com/CatchOrg/Catch2/master/single_include/catch.hpp" ${CATCH_HPP})
endif()

add_subdirectory(redlib)

include(CTest)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

enable_testing()
