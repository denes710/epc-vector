cmake_minimum_required(VERSION 3.16)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Testing)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Add your header files directory
include_directories(include test)

# Add your source files
set(SOURCES
    test/test.cpp
    test/X.cpp
)

# Create an executable
add_executable(test_unit ${SOURCES})

# Link the Boost libraries
target_link_libraries(test_unit Boost::unit_test_framework)