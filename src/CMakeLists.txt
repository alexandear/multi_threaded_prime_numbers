option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
	if (ENABLE_COVERAGE)
	  add_compile_options(--coverage -O0)
	endif()
endif()

add_library(Red PrimeNumberGenerator.cpp Xml.cpp Utils.cpp)
set_target_properties(Red PROPERTIES CXX_STANDARD 17)
target_include_directories(Red PUBLIC .)
if (ENABLE_COVERAGE)
  target_link_libraries(Red --coverage)
endif()

add_executable(prime main.cpp)
set_target_properties(prime PROPERTIES CXX_STANDARD 17)
target_link_libraries(prime LINK_PUBLIC Red)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../data/simple.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
