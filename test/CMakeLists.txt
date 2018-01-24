project(primeTest)

set(CATCH_HPP "${CMAKE_BINARY_DIR}/test/catch.hpp")

if(NOT EXISTS ${CATCH_HPP})
  message(STATUS "Downloading catch.hpp from https://github.com/CatchOrg/Catch")
  file(DOWNLOAD "https://raw.githubusercontent.com/CatchOrg/Catch2/master/single_include/catch.hpp" ${CATCH_HPP})
endif()

file(GLOB_RECURSE TEST_SOURCES "*.h" "*.cpp")

include(CTest)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(${CMAKE_BINARY_DIR}/test ${SOURCE_DIRECTORY})
add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} redlib)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

add_test(PrimeTest ${PROJECT_NAME})

enable_testing()
