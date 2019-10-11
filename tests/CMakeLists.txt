cmake_minimum_required(VERSION 3.0.0)

set(PROJECT algo_tests)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 17)
set(HEADERS ../src/data.h)
set(SOURCES test.cpp main.cpp ../src/data.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT} Threads::Threads)
target_link_libraries(algo_tests ${GTEST_LIBRARIES} pthread)

if(MSVC)
  target_compile_options(${PROJECT} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
