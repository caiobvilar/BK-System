#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <json/json.h> // Assuming you are using the JsonCpp library
#include <string>

class ConfigManager
{
  public:
    ConfigManager(const std::string& configFilePath);
    ~ConfigManager();

    bool loadConfig();
    Json::Value getConfigValue(const std::string& key) const;

  private:
    std::string configFilePath;
    Json::Value configData;
};

#endif // CONFIGMANAGER_HPP