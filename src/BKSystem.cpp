#include "BKSystem.hpp"

BKSystem::BKSystem(const std::string& config_file_path)
    : configManager(ConfigurationManager::getInstance())
{
    done = false;
    conn = nullptr;
    window = nullptr;
    renderer = nullptr;
    if (this->configManager.loadConfig("config.json") < 0)
    {
        spdlog::error("Failed to load the configuration file.");
    } else
    {
        spdlog::info("Configuration file loaded successfully.");
        this->setDatabaseHost(this->configManager.getDatabaseHost());
        this->setDatabaseUser(this->configManager.getDatabaseUser());
        this->setDatabasePassword(this->configManager.getDatabasePassword());
        this->setDatabaseName(this->configManager.getDatabaseName());
        this->setDatabasePort(this->configManager.getDatabasePort());
        this->setDatabaseSocket(this->configManager.getDatabaseSocket());

        if (this->init() < 0)
        {
            spdlog::error("Failed to initialize the BKSystem.");
        }
    }
}

BKSystem::~BKSystem() {}

void BKSystem::draw_led_indicator(MYSQL* conn)
{

    bool is_connected = false;
    if (mysql_ping(this->getConn()) == 0)
    {
        is_connected = true;
    } else
    {
        is_connected = false;
    }
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    float radius = 10.0f;
    ImU32 color =
        is_connected ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255);
    draw_list->AddCircleFilled(
        ImVec2(p.x + radius, p.y + radius), radius, color);
    ImGui::Dummy(
        ImVec2(radius * 2, radius * 2)); // Add some space after the circle
}

void BKSystem::run()
{

    this->done = false;
    while (!this->done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                this->done = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
            {
                this->done = true;
            }
            ImGui_ImplSDL2_ProcessEvent(&event);
        }

        // Start the ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create a simple window
        ImGui::Begin("Hello, world!");
        // Draw the database name
        ImGui::Text("Database Name: %s", this->databaseName.c_str());
        ImGui::Text("Database User: %s", this->databaseUser.c_str());
        ImGui::Text("Database Host: %s", this->databaseHost.c_str());
        ImGui::Text("Database Port: %d", this->databasePort);
        ImGui::Text("Database Socket: %s", this->databaseSocket.c_str());
        // Draw the LED indicator
        draw_led_indicator(this->conn);

        ImGui::End();

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(this->renderer, 114, 144, 154, 255);
        SDL_RenderClear(this->renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),
                                              this->renderer);
        SDL_RenderPresent(this->renderer);
    }
    this->cleanup();
}

void BKSystem::cleanup()
{

    this->done = true;
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    // Close the connection
    mysql_close(this->getConn());
    spdlog::info("Database connection closed.");
    spdlog::info("Closing the BK Server...");
}

int BKSystem::init()
{
    this->window = SDL_CreateWindow("BK Server",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    1280,
                                    720,
                                    SDL_WINDOW_RESIZABLE);
    if (this->window == NULL)
    {
        spdlog::error("Error: {}", SDL_GetError());
        this->cleanup();
        return -1;
    }
    this->renderer = SDL_CreateRenderer(
        this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == NULL)
    {
        spdlog::error("Error: {}", SDL_GetError());
        this->cleanup();
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); // Initialize ImGui
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(this->window, this->renderer);
    ImGui_ImplSDLRenderer2_Init(this->renderer);

    // Initialize MySQL library
    this->conn = mysql_init(NULL);
    if (this->conn == NULL)
    {
        spdlog::error("mysql_init() failed");
        return -1;
    }
    // Disable SSL verification
    my_bool ssl_verify = false;
    mysql_options(this->conn, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &ssl_verify);
    // Connect to the database
    if (mysql_real_connect(this->getConn(),
                           this->getDatabaseHost().c_str(),
                           this->getDatabaseUser().c_str(),
                           this->getDatabasePassword().c_str(),
                           this->getDatabaseName().c_str(),
                           this->getDatabasePort(),
                           this->getDatabaseSocket().c_str(),
                           0) == NULL)
    {
        spdlog::error("mysql_real_connect() failed: {}", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    return 0;
}
