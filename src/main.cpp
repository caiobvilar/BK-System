#include "BKSystem.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        spdlog::error("Usage: {} <config_file_path>", argv[0]);
        return -1;
    }
    spdlog::info(" Starting the BK Server...");
    BKSystem* bkSystem = nullptr;
    bkSystem = new BKSystem(std::string(argv[1]));

    if (bkSystem == nullptr)
    {
        spdlog::error("Failed to create the BKSystem object.");
        delete bkSystem;
        return -1;
    } else
    {
        bkSystem->run();
    }

    // Perform database operations here
    // Main loop
}
