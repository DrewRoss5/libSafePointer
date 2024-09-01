cmake_minimum_required(VERSION 3.10)
project(LibSafePointer)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(SafePointer STATIC
    src/safe_ptr.hpp
)

set_target_properties(SafePointer PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(SafePointer PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# uncomment this to build a demo executable
#add_executable(demo src/main.cpp )