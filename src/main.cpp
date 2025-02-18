#include "iostream"
#include <spdlog/spdlog.h>

#define HOST "localhost"
#define USER
#define PASSWORD
#define DATABASE
#define PORT

int main()
{
    spdlog::info(" Starting the BK Server...");
    spdlog::info("Welcome to spdlog!");
    spdlog::info("Loading the configuration...");
    spdlog::info("Connecting to the database...");
    spdlog::info("Server is running...");
    spdlog::info("Accepting new connections...");
    spdlog::info("Closing the BK Server...");
    return 0;
}