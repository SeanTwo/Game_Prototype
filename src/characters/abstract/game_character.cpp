#include "game_character.h"

game_character::game_character(
    std::string texture_path,
    Vector2 initial_position,
    const window_config& screen,
    std::array<float, 2> frame_mult,
    int chara_id
)
{
    char_texture = LoadTexture(texture_path.c_str());
    frame_width = (float)char_texture.width;
    frame_height = (float)char_texture.height;
    source_rec = { initial_position.x, initial_position.y, frame_width, frame_height };
    dest_rec = { screen.width*screen.multiplier[0], screen.height*screen.multiplier[1], frame_width*frame_mult[0], frame_height*frame_mult[1] };
    origin = { frame_width, frame_height };
    rotation = 0.0f;
    this->chara_id = chara_id;
}

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

void game_character::unload_character()
{
    UnloadTexture(char_texture);
}


