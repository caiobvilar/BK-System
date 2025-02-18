#include "iostream"
#include <mariadb/mysql.h>
#include <spdlog/spdlog.h>

#define HOST "localhost"
#define USER "SERVER"
#define PASSWORD "LP5u!2mre6PcJyg#q$2$#2F%4oV36fiVCaSE*H^QM2"
#define DATABASE "bksysDB"
#define PORT 3306
#define SOCKET "/var/lib/mysql/mysql.sock"

int main()
{
    spdlog::info(" Starting the BK Server...");
    spdlog::info("Welcome to spdlog!");
    spdlog::info("Loading the configuration...");
    // Initialize MySQL library
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        spdlog::error("mysql_init() failed");
        return EXIT_FAILURE;
    }
    // Disable SSL verification
    my_bool ssl_verify = false;
    mysql_options(conn, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &ssl_verify);
    // Connect to the database
    if (mysql_real_connect(
            conn, HOST, USER, PASSWORD, DATABASE, PORT, SOCKET, 0) == NULL)
    {
        spdlog::error("mysql_real_connect() failed: {}", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    spdlog::info("Connected to the database successfully!");
    spdlog::info("Server is running...");
    spdlog::info("Accepting new connections...");

    // Perform database operations here

    // Close the connection
    mysql_close(conn);
    spdlog::info("Database connection closed.");
    spdlog::info("Closing the BK Server...");
    return 0;
}