// 1. Define NOGDI to prevent Windows from loading conflicting macro names
#define NOGDI 
// 2. If you also need to avoid other conflicts down the line, define this too:
#define NOUSER

#include <raylib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <format>
#include <iostream>
#include <array>
#include <math.h>
#include "game_window.h"
#include "game_character.h"
#include "tile.h"

int main()
{
    std::string window_name = "Origin";
    window_config game_window = {640, 480, window_name.c_str()};
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(game_window.width, game_window.height, game_window.window_name);
	DisableEventWaiting(); // Disable waiting for events on EndDrawing() to allow for smoother input handling
    SetTargetFPS(60);
    SetExitKey(KEY_NULL); // Disable default exit key (ESC) to prevent exiting using it
    
    Color default_bg = {0, 0, 0, 255};
    int world_grid_size = 16; // The size of a single tile in the world in pixels

    std::array<float, 2> sprite_scale = {1.0f, 1.0f};

    std::vector<game_character*> characters = { 
        new game_character("resources/textures/characters/slime.png", {0.0f, 0.0f}, game_window, sprite_scale, 1, 16, 16, world_grid_size)
    };
    
    Texture2D current_spritesheet = LoadTexture("resources/textures/spritesheets/test_spritesheet.png");
    std::vector<tile*> tiles = { 
        new tile(&current_spritesheet, 0, 0, game_window, world_grid_size, {0, 0}, sprite_scale),
        new tile(&current_spritesheet, 1, 0, game_window, world_grid_size, {1, 0}, sprite_scale),
        new tile(&current_spritesheet, 1, 1, game_window, world_grid_size, {1, 0}, sprite_scale),
    };

    int current_char = 0;

    game_character* player = characters[current_char];

    //Rectangle dest_rec = { game_window.width*0.5f, game_window.height*0.5f, 16.0f*4.0f, 16.0f*4.0f };

    // Controls player Speed
    const float speed = 4.0f;
    const float default_zoom = 4.0f;

    // Camera Initialization
    Camera2D camera = { 0 };
    camera.target = { player->get_bounding_rect_x()-(player->get_sprite_width()*0.5f), player->get_bounding_rect_y() };
    camera.offset = { GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
    camera.rotation = 0.0f;
    camera.zoom = default_zoom;

    /* Center Each character on the screen (based on their sprite size)
    std::for_each(characters.begin(), characters.end(), [game_window](game_character& entity) 
        { entity.set_pos((game_window.width / 2 - entity.get_entity_width()), (game_window.height / 2 - entity.get_entity_height())); }
    );
    */

    float last_time = GetFrameTime();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(default_bg);
        
        camera.target = { player->get_bounding_rect_x()-(player->get_sprite_width()*0.5f), player->get_bounding_rect_y() };

        // Draw all objects for the world in camera
        BeginMode2D(camera);
            Vector2 mouse_world_pos = GetMousePosition();
            std::for_each(tiles.begin(), tiles.end(), [](tile* tile) { tile->draw(); });

            player->draw();
        EndMode2D();

        std::string mouse_pos = std::to_string(mouse_world_pos.x) + " " + std::to_string(mouse_world_pos.y);

        std::string coords = std::to_string(player->get_x_coord()) + " " + std::to_string(player->get_y_coord());
        DrawText("Character Coordinates", 20, 20, 20, WHITE);
        DrawText(coords.c_str(), 20, 60, 20, WHITE);
        DrawText(mouse_pos.c_str(), 20, 100, 20, WHITE);
        DrawText(std::to_string(GetScreenHeight()).c_str(), 20, 120, 20, WHITE);
        
        if (IsKeyDown(KEY_A))
        {player->move(left, speed, GetFrameTime());}
        if (IsKeyDown(KEY_D))
        {player->move(right, speed, GetFrameTime());}
        if (IsKeyDown(KEY_S))
        {player->move(down, speed, GetFrameTime());}
        if (IsKeyDown(KEY_W))
        {player->move(up, speed, GetFrameTime());}

        if (IsKeyDown(KEY_R))
        {player->set_pos(0, 0);}

        // Camera Reset
        if (IsKeyPressed(KEY_I))
        { 
            camera.zoom = default_zoom*(float)GetScreenHeight()/game_window.height;
        }
        
        // Toggle Full Screen
        if (IsKeyPressed(KEY_F4))
        {
            ToggleFullscreen();
            camera.offset = { GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
            camera.zoom = default_zoom * (float)GetScreenHeight()/game_window.height;
        }


        if (IsKeyPressed(KEY_V))
        {player->set_spritesheet_frame({1>>player->get_spritesheet_col(), 0});}

        EndDrawing();
    }

    std::for_each(characters.begin(), characters.end(), [](game_character* entity) { delete entity; });
    UnloadTexture(current_spritesheet);
    
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