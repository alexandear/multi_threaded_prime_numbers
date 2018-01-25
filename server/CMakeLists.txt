project(server)

file(GLOB_RECURSE APP_SOURCE "*.h" "*.cpp")

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(${PROJECT_NAME} ${APP_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC redlib)
