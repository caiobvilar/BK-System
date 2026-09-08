cmake_minimum_required(VERSION 3.10)

add_library(
    ConfigurationManager STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ConfigurationManager.cpp
)

target_include_directories(ConfigurationManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(
    ConfigurationManager
    PUBLIC
    nlohmann_json::nlohmann_json
    PRIVATE
    spdlog::spdlog
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ConfigurationManager PRIVATE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ConfigurationManager PRIVATE /W4 /WX)
endif()
