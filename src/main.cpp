// 1. Define NOGDI to prevent Windows from loading conflicting macro names
#define NOGDI 
// 2. If you also need to avoid other conflicts down the line, define this too:
#define NOUSER

#include <raylib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "game_window.h"
#include "game_character.h"

#include <vector>

int main()
{
    std::string window_name = "Game Test";
    window_config game_window = {640, 480, {0.5f, 0.5f}, window_name.c_str()};

    InitWindow(game_window.width, game_window.height, game_window.window_name);
	DisableEventWaiting();
    SetTargetFPS(60);
    
    Color default_bg = {0, 0, 0, 255};

    std::vector<game_character> characters = { 
        game_character("resources/textures/characters/slime.png", {0.0f, 0.0f}, game_window, {4.0f, 4.0f}, 1),
        game_character("resources/textures/characters/slime_yellow.png", {0.0f, 0.0f}, game_window, {4.0f, 4.0f}, 2) 
    };

    game_character& player = characters[0];

    Rectangle dest_rec = { game_window.width*game_window.multiplier[0], game_window.height*game_window.multiplier[1], 16.0f*4.0f, 16.0f*4.0f };

    const int speed = 64.0f;

    player.set_pos(game_window.width/2 - player.get_texture_width(), game_window.height/2 - player.get_texture_height());

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(default_bg);
    
        std::for_each(characters.begin(), characters.end(), [](game_character entity) { entity.draw(); });
        
        DrawLine((int)dest_rec.x, 0, (int)dest_rec.x, game_window.height, GRAY);
        DrawLine(0, (int)dest_rec.y, game_window.width, (int)dest_rec.y, GRAY);

        std::string coords = std::to_string(characters[0].get_dest_rect().x) + " " + std::to_string(characters[0].get_dest_rect().y);
        DrawText("Character Coordinates", 20, 20, 20, WHITE);
        DrawText(coords.c_str(), 20, 60, 20, WHITE);
        
        if (IsKeyDown(KEY_A))
        {player.move(left, speed, GetFrameTime());}
        else if (IsKeyDown(KEY_D))
        {player.move(right, speed, GetFrameTime());}
        else if (IsKeyDown(KEY_S))
        {characters[0].move(down, speed, GetFrameTime());}
        else if (IsKeyDown(KEY_W))
        {player.move(up, speed, GetFrameTime());}

        if (IsKeyDown(KEY_R))
        {player.set_pos(game_window.width/2 - player.get_texture_width(), game_window.height/2 - player.get_texture_height());};

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