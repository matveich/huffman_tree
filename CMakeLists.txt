cmake_minimum_required(VERSION 3.10)
project(huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/library)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_library(huffman-library STATIC
        library/tree.h
        library/tree.cpp
        library/bit_sequence.h
        library/bit_sequence.cpp
        library/basic_coder.h
        library/basic_coder.cpp
        library/encoder.h
        library/encoder.cpp
        library/decoder.h
        library/decoder.cpp
        )


add_executable(huffman
        utility/utility.cpp
        )

add_executable(huffman-testing
        tests/gtest/gtest-all.cc
        tests/gtest/gtest.h
        tests/gtest/gtest_main.cc
        tests/testing.cpp
        )

target_link_libraries(huffman huffman-library)
target_link_libraries(huffman-testing huffman-library -lpthread)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()