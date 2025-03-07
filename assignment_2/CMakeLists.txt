cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ASDFR_2)

# Add executable
add_executable(main
    src/main.cpp
    src/q1.cpp
    src/q2.cpp
    # Add other source files here
)

# Include directories
target_include_directories(main PRIVATE include)