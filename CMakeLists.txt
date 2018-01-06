cmake_minimum_required(VERSION 3.2)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(prime main.cpp)
set_target_properties(prime PROPERTIES CXX_STANDARD 17)
