cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BK-System VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(third-party)
add_subdirectory(DBHandler)
add_subdirectory(Reports)

add_library(libDBHandler STATIC DBHandler/Implementation/src/DBHandlerImpl.cpp)
target_include_directories(
    libDBHandler
    PUBLIC
    DBHandler/Core/include
    DBHandler/Implementation/include
    DBHandler/MariaDB/include)
# Add an executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    libDBHandler
)
add_library(ConfigManager STATIC src/ConfigManager.cpp)
target_include_directories(
    ConfigManager
    PUBLIC
    src/include
)

add_library(ReportGenerator STATIC Reports/ReportGenerator.cpp)
target_include_directories(
    ReportGenerator
    PUBLIC
    Reports/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ConfigManager
    ReportGenerator
)