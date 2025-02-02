#ifndef __IDBCLIENT__HPP__
#define __IDBCLIENT__HPP__

#include <memory>
#include <string>
#include <vector>

class IDBCLient
{
  public:
    virtual ~IClientDatabase() = default;

    // Connect to the remote server
    virtual void connect(const std::string& serverUrl,
                         const ErrorCallback& onError) = 0;

    // Disconnect from the remote server
    virtual void disconnect() = 0;

    // Execute a query (e.g., SELECT) asynchronously
    virtual void executeQuery(const std::string& query,
                              const QueryCallback& onSuccess,
                              const ErrorCallback& onError) = 0;

    // Execute a command (e.g., INSERT, UPDATE, DELETE) asynchronously
    virtual void executeCommand(const std::string& command,
                                const CommandCallback& onSuccess,
                                const ErrorCallback& onError) = 0;

    // Check if the client is connected to the server
    virtual bool isConnected() const = 0;
};
#endif //__IDBCLIENT__HPP__