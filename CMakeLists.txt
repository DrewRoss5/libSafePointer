cmake_minimum_required(VERSION 3.10)
project(LibSafePointer)

set(CMAKE_CXX_STANDARD 17)

# configure the library
add_library(SafePointer STATIC
    src/safe_ptr.hpp
)
set_target_properties(SafePointer PROPERTIES LINKER_LANGUAGE CXX)

# configure the tests
find_package(GTest)
include(GoogleTest)
add_executable(tests 
    test/main_test.cpp 
    src/safe_ptr.hpp
)
target_link_libraries(tests PRIVATE GTest::gtest)
