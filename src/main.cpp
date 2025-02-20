#include "../bindings/imgui_impl_sdl2.h"
#include "../bindings/imgui_impl_sdlrenderer2.h"
#include "iostream"
#include <SDL2/SDL.h>
#include <imgui.h>
#include <mariadb/mysql.h>
#include <spdlog/spdlog.h>
#define HOST "localhost"
#define USER "SERVER"
#define PASSWORD "LP5u!2mre6PcJyg#q$2$#2F%4oV36fiVCaSE*H^QM2"
#define DATABASE "bksysDB"
#define PORT 3306
#define SOCKET "/var/lib/mysql/mysql.sock"

void do_imgui_stuff(SDL_Renderer* sdl2renderer);
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
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
        0)
    {
        spdlog::error("Error: {}", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow("BK Server",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1280,
                                          720,
                                          SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        spdlog::error("Error: {}", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        spdlog::error("Error: {}", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    // Initialize ImGui backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Main loop
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                done = true;
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
        do_imgui_stuff(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // Close the connection
    mysql_close(conn);
    spdlog::info("Database connection closed.");
    spdlog::info("Closing the BK Server...");
    return 0;
}
void do_imgui_stuff(SDL_Renderer* sdl2renderer)
{

    // Start the ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Create a simple window
    ImGui::Begin("Hello, world!");
    // Display stuff on window
    ImGui::Text("This is some useful text.");
    // Close window
    ImGui::End();

    // Rendering
    ImGui::Render();
    SDL_SetRenderDrawColor(sdl2renderer, 114, 144, 154, 255);
    SDL_RenderClear(sdl2renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), sdl2renderer);
    SDL_RenderPresent(sdl2renderer);
}