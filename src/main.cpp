// 1. Define NOGDI to prevent Windows from loading conflicting macro names
#define NOGDI 
// 2. If you also need to avoid other conflicts down the line, define this too:
#define NOUSER

#include <string>
#include <algorithm>
#include <vector>
#include <format>
#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>
#include <math.h>
#include <raylib.h>
#include <nlohmann/json.hpp>
#include "game_window.h"
#include "entity.h"
#include "tile.h"
using json = nlohmann::json;

int main()
{
    std::string window_name = "Origin";
    window_config game_window = {640, 480, window_name.c_str()};
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(game_window.width, game_window.height, game_window.window_name);
	DisableEventWaiting(); // Disable waiting for events on EndDrawing() to allow for smoother input handling
    SetTargetFPS(60);
    SetExitKey(KEY_NULL); // Disable default exit key (ESC) to prevent exiting using it
    
    //load json file
    std::ifstream file("resources/maps/map1.json");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string json_text;
    std::string line;
    while (std::getline(file, line)) {
        json_text = json_text + line + "\n" ;
    }

    json map_dat = json::parse(json_text);

    // World based rules and whatnot
    Color default_bg = {
        map_dat["bg_r"],
        map_dat["bg_g"],
        map_dat["bg_b"],
        map_dat["bg_a"]
    };
    int world_grid_size = map_dat["world_grid_size"]; // The size of a single tile in the world in pixels
    std::array<float, 2> sprite_scale = {map_dat["def_spr_scl_x"], map_dat["def_spr_scl_y"]};
    Vector2 initial_player_spawn = {map_dat["spawn_x"], map_dat["spawn_y"]};


    std::string tileset_sprite = map_dat["tileset_sprite_sheet"];
    Texture2D current_spritesheet = LoadTexture(tileset_sprite.c_str());
    std::vector<tile*> tiles;
    for (auto& map_tile : map_dat["tiles"].items())
    {
        auto tile_doc = map_tile.value();
        tiles.insert(tiles.end(), new tile(&current_spritesheet, tile_doc["x"], tile_doc["y"], game_window, world_grid_size, {tile_doc["tm_col"], tile_doc["tm_row"]}, sprite_scale));
    }

    std::vector<entity*> entities = { 
        new entity("resources/textures/characters/slime.png", initial_player_spawn, game_window, sprite_scale, 1, 16, 16, world_grid_size)
    };

    int current_char = 0;

    entity* player = entities[current_char];

    //Rectangle dest_rec = { game_window.width*0.5f, game_window.height*0.5f, 16.0f*4.0f, 16.0f*4.0f };

    // Controls player Speed
    const float speed = 4.0f;
    const float default_zoom = 4.0f;

    // Camera Initialization
    Camera2D camera = { 0 };
    camera.target = { 
        player->get_bounding_rect_x()-(player->get_sprite_width()*0.5f), 
        player->get_bounding_rect_y()-(player->get_sprite_height()*0.5f)
    };
    camera.offset = { GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
    camera.rotation = 0.0f;
    camera.zoom = default_zoom;

    float last_time = GetFrameTime();

    int monitor_id = GetCurrentMonitor();
    int monitor_height = GetMonitorHeight(monitor_id);
    int monitor_width = GetMonitorWidth(monitor_id);
    int border_bar_width = (monitor_width-(1.3333333333f*monitor_height))/2;
    int viewport_width = monitor_width - (border_bar_width*2);

    // Shader setup
    Shader crt_shader = LoadShader(0, "resources/shaders/crt.fs");
    bool shaderActive = false; // shader is disabled by default
    Image blankImage = GenImageColor(1, 1, {0,0,0,120});
    Texture2D blankTexture = LoadTextureFromImage(blankImage);
    UnloadImage(blankImage); // Free RAM

    while (!WindowShouldClose())
    {
        
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(0, 0) < -0.8 )
        {player->move(left, speed, GetFrameTime());}
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(0, 0) > 0.8)
        {player->move(right, speed, GetFrameTime());}
        else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(0, 1) > 0.8)
        {player->move(down, speed, GetFrameTime());}
        else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || GetGamepadAxisMovement(0, 1) < -0.8)
        {player->move(up, speed, GetFrameTime());}
        
        // Toggle Full Screen
        if (IsKeyPressed(KEY_F4))
        {   
            // Account for if game window has moved to another monitor to adjust full screen 4:3 blackbars
            monitor_id = GetCurrentMonitor();
            monitor_height = GetMonitorHeight(monitor_id);
            monitor_width = GetMonitorWidth(monitor_id);
            border_bar_width = (monitor_width-(1.3333333333f*monitor_height))/2;
            viewport_width = monitor_width - (border_bar_width*2);
            // Do the actual full screen toggle and adjustment
            DrawRectangle(0, 0, monitor_width, monitor_height, BLACK); // Black out screen during transition to fullscreen
            ToggleFullscreen();
            camera.offset = { GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
            camera.zoom = default_zoom * (float)GetScreenHeight()/game_window.height;
        }

        //Developer Controls
        if (IsKeyDown(KEY_R))
        {player->set_pos(0, 0);}

        // Camera Controls
        if (IsKeyPressed(KEY_O))
        { camera.zoom += 1.0f; }
        if (IsKeyPressed(KEY_P))
        { camera.zoom -= 1.0f; }
        if (IsKeyPressed(KEY_I))
        { camera.zoom = default_zoom*(float)GetScreenHeight()/game_window.height; }

        if (IsKeyPressed(KEY_V))
        {player->set_spritesheet_frame({1>>player->get_spritesheet_col(), 0});}
        
        if (IsKeyPressed(KEY_F7))
        { shaderActive = !shaderActive; }
        // End Dev Controls

        BeginDrawing();
        ClearBackground(default_bg);
        
        camera.target = { 
            player->get_bounding_rect_x()-(player->get_sprite_width()*0.5f), 
            player->get_bounding_rect_y()-(player->get_sprite_height()*0.5f)
        };
        
            // Draw all objects for the world in camera
            BeginMode2D(camera);
                std::for_each(tiles.begin(), tiles.end(), [](tile* tile) { tile->draw(); });

                std::for_each(entities.begin(), entities.end(), [](entity* entity) { entity->draw(); });
            EndMode2D();

            // Draw black bars if fullscreen
            if(IsWindowFullscreen()){
                DrawRectangle(monitor_width-border_bar_width, 0, border_bar_width, monitor_height, BLACK);
                DrawRectangle(0, 0, border_bar_width, monitor_height, BLACK);
                
                //Crt Shader across full viewport
                if(shaderActive)
                {
                    BeginShaderMode(crt_shader);
                        DrawTextureEx(blankTexture, { (float)border_bar_width, 0 }, 0.0f, (float)viewport_width, {255,255,255,120});
                        //DrawRectangle(border_bar_width, 0, viewport_width, monitor_height, {0,0,0,150});
                    EndShaderMode();
                }
            }
        
        // Dev Stats Drawing
        std::string coords = std::to_string(player->get_x_coord()) + " " + std::to_string(player->get_y_coord());
        std::string zoom_str = std::to_string(camera.zoom);
        std::string gamepad_axis = std::to_string(GetGamepadAxisMovement(0, 0)) + " " + std::to_string(GetGamepadAxisMovement(0, 1));
        std::string gamepads_available = "Gamepad 1: " + std::to_string(IsGamepadAvailable(0)) + " Gamepad 2: " + std::to_string(IsGamepadAvailable(1));
        int font_size = 10;

        DrawText("Character Coordinates", 20, 20, font_size, WHITE);
        DrawText(coords.c_str(), 20, 40, font_size, WHITE);
        DrawText(zoom_str.c_str(), 20, 60, font_size, WHITE);
        DrawText(std::to_string(GetScreenHeight()).c_str(), 20, 80, font_size, WHITE);
        DrawText(std::to_string(GetGamepadButtonPressed()).c_str(), 20, 100, font_size, WHITE);
        DrawText(GetGamepadName(0), 20, 120, font_size, WHITE);
        DrawText(std::to_string(GetGamepadAxisCount(0)).c_str(), 20, 140, font_size, WHITE);
        DrawText(gamepad_axis.c_str(), 20, 160, font_size, WHITE);
        DrawText(gamepads_available.c_str(), 20, 180, font_size, WHITE);

        EndDrawing();
    }

    std::for_each(entities.begin(), entities.end(), [](entity* entity) { delete entity; });
    UnloadTexture(current_spritesheet);
    UnloadTexture(blankTexture);
    
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