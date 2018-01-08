option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if (ENABLE_COVERAGE)
  add_compile_options(--coverage -O0)
endif()
add_compile_options(-Wall -Wextra -Wpedantic)

add_library(Red PrimeNumberGenerator.cpp)
set_target_properties(Red PROPERTIES CXX_STANDARD 17)
target_include_directories(Red PUBLIC .)
if (ENABLE_COVERAGE)
  target_link_libraries(Red --coverage)
endif()

add_executable(prime main.cpp)
set_target_properties(prime PROPERTIES CXX_STANDARD 17)
target_link_libraries(prime LINK_PUBLIC Red)
