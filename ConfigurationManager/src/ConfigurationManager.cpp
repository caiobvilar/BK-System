#include "../include/ConfigurationManager.hpp"
#include "ConfigurationManager.hpp"
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>

ConfigurationManager::ConfigurationManager(const std::string& filePath)
{
    if (!filePath.empty())
    {
        loadConfig(filePath);
    }
}

/**
 * @brief Retrieves the singleton instance of ConfigurationManager.
 *
 * This function returns the singleton instance of the ConfigurationManager
 * class. If the instance does not exist, it will be created using the provided
 * file path.
 *
 * @param filePath The path to the configuration file.
 * @return A reference to the singleton instance of ConfigurationManager.
 */
ConfigurationManager&
ConfigurationManager::getInstance(const std::string& filePath)
{
    static ConfigurationManager instance(filePath);
    return instance;
}

nlohmann::json ConfigurationManager::getConfig() const { return configData; }

int ConfigurationManager::loadConfig(const std::string& filePath)
{
    std::ifstream configFile(filePath);
    if (!configFile.is_open())
    {
        spdlog::error("Could not open the config file: {}", filePath);
        return -1;
    }
    try
    {
        configFile >> configData;
    } catch (const nlohmann::json::parse_error& e)
    {
        spdlog::error("Error parsing the config file: {}", e.what());
        return -1;
    }
    return 0;
}

// Database configuration getters and setters
std::string ConfigurationManager::getDatabaseHost() const
{
    if (this->configData["database"]["host"].is_null())
    {
        return "";
    }
    return this->configData["database"]["host"];
}

void ConfigurationManager::setDatabaseHost(const std::string& host)
{
    this->configData["database"]["host"] = host;
}

std::string ConfigurationManager::getDatabaseUser() const
{
    return this->configData["database"]["user"];
}

void ConfigurationManager::setDatabaseUser(const std::string& user)
{
    this->configData["database"]["user"] = user;
}

std::string ConfigurationManager::getDatabasePassword() const
{
    return this->configData["database"]["password"];
}

void ConfigurationManager::setDatabasePassword(const std::string& password)
{
    this->configData["database"]["password"] = password;
}

int ConfigurationManager::getDatabasePort() const
{
    return this->configData["database"]["port"];
}

void ConfigurationManager::setDatabasePort(int port)
{
    this->configData["database"]["port"] = port;
}

std::string ConfigurationManager::getDatabaseName() const
{
    return this->configData["database"]["database_name"];
}

void ConfigurationManager::setDatabaseName(const std::string& name)
{
    this->configData["database"]["database_name"] = name;
}

std::string ConfigurationManager::getDatabaseSocket() const
{
    return this->configData["database"]["socket"];
}

void ConfigurationManager::setDatabaseSocket(const std::string& socket)
{
    this->configData["database"]["socket"] = socket;
}
