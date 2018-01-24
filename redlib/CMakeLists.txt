project(redlib)

find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(INCLUDE_DIRECTORY "include")
set(SOURCE_DIRECTORY "src")

file(GLOB_RECURSE LIB_SOURCE "*.h" "*.cpp")

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

include_directories(${INCLUDE_DIRECTORY})
add_library(${PROJECT_NAME} ${LIB_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORY})
if (ENABLE_COVERAGE)
  target_link_libraries(${PROJECT_NAME} --coverage Threads::Threads)
else()
  target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()
