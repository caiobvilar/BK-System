#include "ConfigurationManager.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <spdlog/spdlog.h>

ConfigurationManager::ConfigurationManager(const std::string& filePath)
{
    spdlog::info("Creating ConfigurationManager instance...");
    spdlog::info("Loading configuration file: {}", filePath);
}

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
        spdlog::error("Could not open the config file: {} {}",
                      filePath,
                      std::strerror(errno));
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

// Helpers to read a single value out of the "database" section
std::string
ConfigurationManager::getDatabaseString(const std::string& key,
                                        const std::string& def) const
{
    const auto& database =
        configData.value("database", nlohmann::json::object());
    if (database.contains(key) && database[key].is_string())
    {
        return database[key].get<std::string>();
    }
    return def;
}

int ConfigurationManager::getDatabaseInt(const std::string& key, int def) const
{
    const auto& database =
        configData.value("database", nlohmann::json::object());
    if (database.contains(key) && database[key].is_number())
    {
        return database[key].get<int>();
    }
    return def;
}

// Database configuration getters and setters
std::string ConfigurationManager::getDatabaseHost() const
{
    return getDatabaseString("host", "");
}

void ConfigurationManager::setDatabaseHost(const std::string& host)
{
    configData["database"]["host"] = host;
}

std::string ConfigurationManager::getDatabaseUser() const
{
    return getDatabaseString("user", "");
}

void ConfigurationManager::setDatabaseUser(const std::string& user)
{
    configData["database"]["user"] = user;
}

std::string ConfigurationManager::getDatabasePassword() const
{
    return getDatabaseString("password", "");
}

void ConfigurationManager::setDatabasePassword(const std::string& password)
{
    configData["database"]["password"] = password;
}

int ConfigurationManager::getDatabasePort() const
{
    return getDatabaseInt("port", 3306);
}

void ConfigurationManager::setDatabasePort(int port)
{
    configData["database"]["port"] = port;
}

std::string ConfigurationManager::getDatabaseName() const
{
    return getDatabaseString("database_name", "");
}

void ConfigurationManager::setDatabaseName(const std::string& name)
{
    configData["database"]["database_name"] = name;
}

std::string ConfigurationManager::getDatabaseSocket() const
{
    return getDatabaseString("socket", "");
}

void ConfigurationManager::setDatabaseSocket(const std::string& socket)
{
    configData["database"]["socket"] = socket;
}
