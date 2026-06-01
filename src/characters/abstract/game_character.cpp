#include "game_character.h"

//Public Constructor(s)
game_character::game_character(
    std::string texture_path,
    Vector2 initial_position,
    const window_config& screen,
    std::array<float, 2> sprite_scale,
    int chara_id,
    int width_pixels,
    int height_pixels
)
{
    char_texture = LoadTexture(texture_path.c_str());
    frame_width = (float)width_pixels;
    frame_height = (float)height_pixels;
    source_rec = { initial_position.x, initial_position.y, frame_width, frame_height };
    dest_rec = { screen.width*0.5f, screen.height*0.5f, frame_width*sprite_scale[0], frame_height*sprite_scale[1] };
    origin = { frame_width, frame_height };
    rotation = 0.0f;
    this->chara_id = chara_id;
    this->current_spritesheet_pos = { 0, 0 }; // Always default to the first row and column of the spritesheet
}

//Private Functions
void game_character::set_spritesheet_pos(float x, float y)
{
    source_rec.x = x;
    source_rec.y = y;
}

//Public Functions
void game_character::draw()
{
    DrawTexturePro(char_texture, source_rec, dest_rec, origin, rotation, WHITE);
}

void game_character::rotate()
{
    (int)rotation++;
}

void game_character::set_rotation(float rotation_angle)
{
    rotation = rotation_angle;
}

void game_character::move(direction dir, float speed, float dt)
{
    int movement = speed * dt;
    switch (dir) {
        case direction::left:
            dest_rec.x -= movement;
            break;
        case direction::right:
            dest_rec.x += movement;
            break;
        case direction::up:
            dest_rec.y -= movement;
            break;
        case direction::down:
            dest_rec.y += movement;
            break;
    }
}

void game_character::set_pos(float x, float y)
{
    dest_rec.x = x;
    dest_rec.y = y;
}

void game_character::set_spritesheet_frame(sprite_matrix new_sprite_pos)
{
    this->current_spritesheet_pos = new_sprite_pos;
    set_spritesheet_pos(frame_width * new_sprite_pos.col, frame_height * new_sprite_pos.row);
}

// Getters
Texture2D game_character::get_texture()
{
    return char_texture;
}

Rectangle game_character::get_src_rect()
{
    return source_rec;
}

Rectangle game_character::get_dest_rect()
{
    return dest_rec;
}

Vector2 game_character::get_origin()
{
   return origin;
}

float game_character::get_rotation()
{
    return rotation;
}

float game_character::get_entity_width()
{
    return frame_width;
}

float game_character::get_entity_height()
{
    return frame_height;
}

sprite_matrix game_character::get_spritesheet_pos()
{
    return current_spritesheet_pos;
}

int game_character::get_spritesheet_row()
{
    return current_spritesheet_pos.row;
}

int game_character::get_spritesheet_col()
{
    return current_spritesheet_pos.col;
}

// Unloader(s)
void game_character::unload_character()
{
    UnloadTexture(char_texture);
}


