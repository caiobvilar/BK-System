cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BK-System VERSION 0.1 LANGUAGES CXX)

find_package(fmt REQUIRED)
find_package(asio REQUIRED)
find_package(mariadb-connector-c REQUIRED)
find_package(spdlog REQUIRED)
find_package(httplib REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(ZLIB REQUIRED)
add_subdirectory(src)


# Add an executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    fmt::fmt
    asio::asio
    spdlog::spdlog
    httplib::httplib
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    mariadb-connector-c::mariadb-connector-c
    ZLIB::ZLIB
)