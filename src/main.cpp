// 1. Define NOGDI to prevent Windows from loading conflicting macro names
#define NOGDI 
// 2. If you also need to avoid other conflicts down the line, define this too:
#define NOUSER

#include <raylib.h>
#include <string>
#include "game_window.h"
#include "game_character.h"

int main()
{
    std::string window_name = "Game Test";
    window_config game_window = {800, 600, {0.5f, 0.5f}, window_name.c_str()};

    InitWindow(game_window.width, game_window.height, game_window.window_name);
	DisableEventWaiting();
    SetTargetFPS(60);
    
    Color default_bg = {0, 0, 0, 255};

    game_character slime = game_character("resources/textures/characters/slime.png", {0.0f, 0.0f}, game_window, {4.0f, 4.0f}, 1);


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(default_bg);
        
        slime.draw();

        DrawLine((int)slime.get_dest_rect().x, 0, (int)slime.get_dest_rect().x, game_window.height, GRAY);
        DrawLine(0, (int)slime.get_dest_rect().y, game_window.width, (int)slime.get_dest_rect().y, GRAY);

        EndDrawing();
    }
    
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