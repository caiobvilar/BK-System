#ifndef __CONFIGURATIONMANAGER_HPP__
#define __CONFIGURATIONMANAGER_HPP__

#include <nlohmann/json.hpp>
#include <string>

class ConfigurationManager
{
  public:
    static ConfigurationManager& getInstance(const std::string& filePath = "");

    nlohmann::json getConfig() const;
    int loadConfig(const std::string& filePath);

    // Database configuration getters and setters
    std::string getDatabaseHost() const;
    void setDatabaseHost(const std::string& host);

    std::string getDatabaseUser() const;
    void setDatabaseUser(const std::string& user);

    std::string getDatabasePassword() const;
    void setDatabasePassword(const std::string& password);

    int getDatabasePort() const;
    void setDatabasePort(int port);

    std::string getDatabaseName() const;
    void setDatabaseName(const std::string& name);

    std::string getDatabaseSocket() const;
    void setDatabaseSocket(const std::string& socket);

  private:
    ConfigurationManager() = default;
    ConfigurationManager(const std::string& filePath);

    // Delete copy constructor and assignment operator
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    nlohmann::json configData;
};

#endif // __CONFIGURATIONMANAGER_HPP__