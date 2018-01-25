project(clientTest)

set(CLIENT_SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../client)
set(CLIENT_SOURCES ${CLIENT_SOURCES_DIRECTORY}/Client.h ${CLIENT_SOURCES_DIRECTORY}/Client.cpp)

file(GLOB_RECURSE TEST_SOURCES "*.h" "*.cpp")

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(${CMAKE_BINARY_DIR}/test ${CMAKE_CURRENT_SOURCE_DIR}/../../client)
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${CLIENT_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/../CatchConfig.cpp)
target_link_libraries(${PROJECT_NAME} redlib)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

add_test(ClientTest ${PROJECT_NAME})
