#include "ConfigManager.hpp"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager(const std::string& configFilePath)
    : configFilePath(configFilePath)
{
}

ConfigManager::~ConfigManager() {}

bool ConfigManager::loadConfig()
{
    std::ifstream configFile(configFilePath, std::ifstream::binary);
    if (!configFile.is_open())
    {
        std::cerr << "Unable to open config file: " << configFilePath
                  << std::endl;
        return false;
    }

    configFile >> configData;
    configFile.close();
    return true;
}

Json::Value ConfigManager::getConfigValue(const std::string& key) const
{
    return configData[key];
}