cmake_minimum_required(VERSION 3.10)
# Add the library
add_library(
    ConfigurationManager
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ConfigurationManager.cpp 
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


# Link libraries
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
target_link_libraries(ConfigurationManager PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog)

# Set compiler flags to treat all warnings as errors
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ConfigurationManager PRIVATE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ConfigurationManager PRIVATE /W4 /WX)
endif()