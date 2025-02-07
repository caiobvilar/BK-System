
#include <memory>
#include <string>
#include <vector>

/**
 * @class IDBServer
 * @brief Interface for database server operations.
 *
 * This interface defines the basic operations required to interact with a
 * database server. It includes methods for connecting and disconnecting from
 * the database, executing queries and commands, and managing transactions.
 */
class IDBServer
{
  public:
    /**
     * @brief Virtual destructor for the IDatabase interface.
     *
     * This ensures that the destructor of the derived class is called
     * when an object is deleted through a pointer to the base class.
     */
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