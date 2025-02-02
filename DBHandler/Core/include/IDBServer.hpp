
#include <memory>
#include <string>
#include <vector>

class IDBServer
{
  public:
    virtual ~IDatabase() = default;

    // Connect to the database
    virtual void connect(const std::string& connectionString) = 0;

    // Disconnect from the database
    virtual void disconnect() = 0;

    // Execute a query (e.g., SELECT)
    virtual std::vector<std::vector<std::string>>
    executeQuery(const std::string& query) = 0;

    // Execute a command (e.g., INSERT, UPDATE, DELETE)
    virtual void executeCommand(const std::string& command) = 0;

    // Begin a transaction
    virtual void beginTransaction() = 0;

    // Commit the current transaction
    virtual void commitTransaction() = 0;

    // Roll back the current transaction
    virtual void rollbackTransaction() = 0;

    // Check if the connection is active
    virtual bool isConnected() const = 0;
};