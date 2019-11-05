cmake_minimum_required(VERSION 3.15.0)

set(PROJECT algo_bench)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(HEADERS ../src/algo_stack.h ../src/algo_tree.h ../src/algo.h)
set(SOURCES main.cpp ../src/algo_stack.cpp ../src/algo_tree.cpp ../src/algo.cpp)

find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT} Threads::Threads)
target_link_libraries(${PROJECT} benchmark)

#if(MSVC)
#  target_compile_options(${PROJECT} PRIVATE /W4 /WX)
#else()
#  target_compile_options(${PROJECT} PRIVATE -Wall -Wextra -pedantic -Werror)
#endif()
