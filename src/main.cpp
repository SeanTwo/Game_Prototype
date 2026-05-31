// 1. Define NOGDI to prevent Windows from loading conflicting macro names
#define NOGDI 
// 2. If you also need to avoid other conflicts down the line, define this too:
#define NOUSER

#include <raylib.h>
#include <string>
#include <algorithm>
#include <time.h>
#include "game_window.h"
#include "game_character.h"

#include <array>


int main()
{
    std::string window_name = "Game Test";
    window_config game_window = {640, 480, {0.5f, 0.5f}, window_name.c_str()};

    InitWindow(game_window.width, game_window.height, game_window.window_name);
	DisableEventWaiting();
    SetTargetFPS(60);
    
    Color default_bg = {0, 0, 0, 255};

    std::array<game_character, 2> characters = { game_character("resources/textures/characters/slime.png", {0.0f, 0.0f}, game_window, {4.0f, 4.0f}, 1), game_character("resources/textures/characters/slime_yellow.png", {0.0f, 0.0f}, game_window, {4.0f, 4.0f}, 1) };

    game_character slime = characters[0];

    characters[1].set_pos(25.0f, 25.0f);

    clock_t last_time = clock();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(default_bg);
        
        std::for_each(characters.begin(), characters.end(), [](game_character& entity) { entity.draw(); });
        
        DrawLine((int)slime.get_dest_rect().x, 0, (int)slime.get_dest_rect().x, game_window.height, GRAY);
        DrawLine(0, (int)slime.get_dest_rect().y, game_window.width, (int)slime.get_dest_rect().y, GRAY);
        
        //Delta time calculations
        clock_t current_time = clock();
        float dt = (float)(current_time - last_time) / CLOCKS_PER_SEC;
        last_time = current_time;

        // Skip calculations if frame is too fast (0 dt)
        if (dt > 0.0f) {
            characters[0].move(down, 50.0f * dt);
        }
        EndDrawing();
    }

    std::for_each(characters.begin(), characters.end(), [](game_character& entity) { entity.unload_character(); });
    
    CloseWindow();
    return 0;
}

// --- ADD THIS BLOCK FOR COMPATIBILITY ---
#if defined(_WIN32) && defined(NDEBUG)
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main(); // Manually forwards to your standard main function
}
#endif