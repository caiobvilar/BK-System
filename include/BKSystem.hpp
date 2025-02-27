#ifndef __BKSYSTEM_HPP__
#define __BKSYSTEM_HPP__ // Header guard

#include "../ConfigurationManager/include/ConfigurationManager.hpp"
#include "../bindings/imgui_impl_sdl2.h"
#include "../bindings/imgui_impl_sdlrenderer2.h"
#include "iostream"
#include <SDL2/SDL.h>
#include <imgui.h>
#include <mariadb/mysql.h>
#include <spdlog/spdlog.h>

/**
 * @brief The BKSystem class handles the main functionality of the BK Server.
 */
class BKSystem
{
  public:
    /**
     * @brief Constructs a new BKSystem object.
     */
    explicit BKSystem(const std::string& config_file_path);

    /**
     * @brief Destroys the BKSystem object.
     */
    ~BKSystem();

    /**
     * @brief Draws an LED indicator showing the connection status to the
     * database.
     *
     * @param conn The MySQL connection object.
     */
    void draw_led_indicator(MYSQL* conn);

    /**
     * @brief Runs the main loop of the BK Server.
     */
    void run();

    /**
     * @brief Cleans up resources used by the BKSystem.
     */
    void cleanup();

    /**
     * @brief Initializes the BKSystem.
     */
    int init();

    /**
     * @brief Sets the done flag.
     *
     * @param done The new value of the done flag.
     */
    void setDone(bool done) { this->done = done; }

    /**
     * @brief Sets the MySQL connection object.
     *
     * @param conn The MySQL connection object.
     */
    void setConn(MYSQL* conn) { this->conn = conn; }

    /**
     * @brief Sets the SDL window object.
     *
     * @param window The SDL window object.
     */
    void setWindow(SDL_Window* window) { this->window = window; }

    /**
     * @brief Sets the SDL renderer object.
     *
     * @param renderer The SDL renderer object.
     */
    void setRenderer(SDL_Renderer* renderer) { this->renderer = renderer; }

    /**
     * @brief Gets the value of the done flag.
     *
     * @return true if the main loop should exit, false otherwise.
     */
    bool getDone() const
    {
        spdlog::debug("getDone() called");
        return this->done;
    }

    /**
     * @brief Gets the MySQL connection object.
     *
     * @return The MySQL connection object.
     */
    MYSQL* getConn() const
    {
        spdlog::debug("getConn() called");
        return this->conn;
    }

    /**
     * @brief Gets the SDL window object.
     *
     * @return The SDL window object.
     */
    SDL_Window* getWindow() const
    {
        spdlog::debug("getWindow() called");
        return this->window;
    }

    /**
     * @brief Gets the SDL renderer object.
     *
     * @return The SDL renderer object.
     */
    SDL_Renderer* getRenderer() const
    {
        spdlog::debug("getRenderer() called");
        return this->renderer;
    }

    // Database configuration getters and setters
    std::string getDatabaseHost() const
    {
        spdlog::debug("getDatabaseHost() called");
        return this->databaseHost;
    }
    std::string getDatabaseUser() const
    {
        spdlog::debug("getDatabaseUser() called");
        return this->databaseUser;
    }
    std::string getDatabasePassword() const
    {
        spdlog::debug("getDatabasePassword() called");
        return this->databasePassword;
    }
    int getDatabasePort() const
    {
        spdlog::debug("getDatabasePort() called");
        return this->databasePort;
    }
    std::string getDatabaseSocket() const
    {
        spdlog::debug("getDatabaseSocket() called");
        return this->databaseSocket;
    }
    std::string getDatabaseName() const
    {
        spdlog::debug("getDatabaseName() called");
        return this->databaseName;
    }
    void setDatabaseName(const std::string& name) { this->databaseName = name; }
    void setDatabaseHost(const std::string& host) { this->databaseHost = host; }
    void setDatabaseUser(const std::string& user) { this->databaseUser = user; }
    void setDatabasePassword(const std::string& password)
    {
        this->databasePassword = password;
    }
    void setDatabasePort(int port) { this->databasePort = port; }
    void setDatabaseSocket(const std::string& socket)
    {
        this->databaseSocket = socket;
    }

  private:
    MYSQL* conn;            ///< The MySQL connection object.
    SDL_Window* window;     ///< The SDL window object.
    SDL_Renderer* renderer; ///< The SDL renderer object.
    bool done; ///< The flag indicating whether the main loop should exit.
    std::string databaseHost;     ///< The database host.
    std::string databaseUser;     ///< The database user.
    std::string databaseName;     ///< The database name.
    std::string databasePassword; ///< The database password.
    int databasePort;             ///< The database port.
    std::string databaseSocket;   ///< The database socket.

    ConfigurationManager& configManager;
};

#endif // __BKSYSTEM_HPP__