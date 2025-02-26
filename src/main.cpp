#include "BKSystem.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        spdlog::error("Usage: {} <config_file_path>", argv[0]);
        return -1;
    }
    spdlog::info(" Starting the BK Server...");
    BKSystem* bkSystem = new BKSystem(argv[1]);
    bkSystem->run();

    delete bkSystem;
    // Perform database operations here
    // Main loop
}
