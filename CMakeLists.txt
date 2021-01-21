cmake_minimum_required(VERSION 3.17)
project(xxhash_gen)

set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(xxhash_gen main.cpp)
target_link_libraries(xxhash_gen ${CONAN_LIBS})
