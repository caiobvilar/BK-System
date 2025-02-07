cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DBHandler)
add_subdirectory(Core)
add_subdirectory(Implementation)
add_subdirectory(MariaDB)

# Add the static library
add_library(DBHandler STATIC
    Implementation/src/DBHandlerImpl.cpp
    Implementation/include/DBHandlerImpl.hpp
)

# Specify include directories
target_include_directories(DBHandler PUBLIC include)