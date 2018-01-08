cmake_minimum_required(VERSION 3.2)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(Red src/PrimeNumberGenerator.cpp)
set_target_properties(Red PROPERTIES CXX_STANDARD 17)
target_include_directories (Red PUBLIC src)

add_executable(prime src/main.cpp)
set_target_properties(prime PROPERTIES CXX_STANDARD 17)
target_link_libraries (prime LINK_PUBLIC Red)
