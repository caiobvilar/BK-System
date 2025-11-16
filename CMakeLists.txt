cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the project name
project(BK-System VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(bindings)
add_subdirectory(ConfigurationManager)

# Conan packages
find_package(fmt REQUIRED)
find_package(asio REQUIRED)
find_package(spdlog REQUIRED)
find_package(httplib REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(ZLIB REQUIRED)
find_package(imgui REQUIRED)
find_package(Boost REQUIRED)

# System packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Manual MariaDB detection
find_path(MARIADB_INCLUDE_DIR
    NAMES mysql.h
    PATHS 
        /usr/include/mysql
        /usr/include/mariadb
        /usr/local/include/mysql
        /usr/local/include/mariadb
)

find_library(MARIADB_LIBRARY
    NAMES mariadb
    PATHS 
        /usr/lib64
        /usr/lib
        /usr/local/lib
)

if(MARIADB_INCLUDE_DIR AND MARIADB_LIBRARY)
    message(STATUS "Found MariaDB: ${MARIADB_LIBRARY}")
    message(STATUS "MariaDB include: ${MARIADB_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "MariaDB not found")
endif()

add_executable(
    ${PROJECT_NAME}
    src/BKSystem.cpp
    src/main.cpp
    bindings/imgui_impl_sdl2.cpp
    bindings/imgui_impl_sdlrenderer2.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/ConfigManager/include
    ${SDL2_INCLUDE_DIRS}
    ${MARIADB_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    fmt::fmt
    asio::asio
    spdlog::spdlog
    httplib::httplib
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    ZLIB::ZLIB
    ${SDL2_LIBRARIES}
    ${MARIADB_LIBRARY}
    imgui::imgui
    ConfigurationManager
    Boost::boost
)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${SDL2_LIBRARY_DIRS}
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    ${SDL2_CFLAGS_OTHER}
)