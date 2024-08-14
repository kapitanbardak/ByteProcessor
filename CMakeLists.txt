cmake_minimum_required(VERSION 3.24)
project(ByteProcessor)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_library(byte_processor STATIC
        src/ByteProcessor.cpp
        )

# Add a block to find and include GTest before creating the "tests" target
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create the executable "tests" for running tests
add_executable(tests src/test.cpp)

# Specify the path to GTest header files
target_include_directories(tests PRIVATE
        ${GTEST_INCLUDE_DIRS}
        )

# Link the necessary libraries for testing
target_link_libraries(tests PRIVATE
        GTest::GTest
        GTest::Main
        pthread
        )

# Link "tests" with "byte_processor"
target_link_libraries(tests PRIVATE byte_processor)