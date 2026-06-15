#include "game_character.h"

//Public Constructor(s)
game_character::game_character(
    std::string texture_path,
    Vector2 initial_position,
    const window_config& screen,
    std::array<float, 2> sprite_scale,
    int chara_id,
    int width_pixels,
    int height_pixels,
    int world_grid_size // World grid size is the size of a single tile in the world in pixels
)
{
    this->char_texture = LoadTexture(texture_path.c_str());
    this->sprite_width = (float)width_pixels;
    this->sprite_height = (float)height_pixels;
    this->source_rec = { 0.0f, 0.0f, sprite_width, sprite_height };
    this->dest_rec = { sprite_scale[0]*2+initial_position.x, sprite_scale[1]*2+initial_position.y, sprite_width*sprite_scale[0], sprite_height*sprite_scale[1] }; // Sets the initial position of the character based on the initial position passed in, but also accounts for the scaling of the sprite and centers the character on that position
    this->origin = { sprite_width, sprite_height };
    this->rotation = 0.0f;
    this->chara_id = chara_id;
    this->world_grid_size = world_grid_size;
    this->current_spritesheet_pos = { 0, 0 }; // Always default to the first row and column of the spritesheet
    normalize_coordinates();
}

//Private Functions
void game_character::set_spritesheet_pos(float x, float y)
{
    source_rec.x = x;
    source_rec.y = y;
}

void game_character::normalize_coordinates()
{
    this->x = dest_rec.x/world_grid_size;
    this->y = dest_rec.y/world_grid_size;
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
    float movement = speed * dt * world_grid_size;
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
    // Update Normalized Coordinates to 16x16 grid
    normalize_coordinates();
}

void game_character::set_pos(float x, float y)
{
    dest_rec.x = x*world_grid_size;
    dest_rec.y = y*world_grid_size;
    normalize_coordinates();
}

void game_character::set_spritesheet_frame(sprite_matrix new_sprite_pos)
{
    this->current_spritesheet_pos = new_sprite_pos;
    set_spritesheet_pos(sprite_width * new_sprite_pos.col, sprite_height * new_sprite_pos.row);
}

// Getters
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

float game_character::get_x_coord()
{
    return x;
}

float game_character::get_y_coord()
{
    return y;
}

// Getters for raylib focused character attributes
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

float game_character::get_sprite_width()
{
    return sprite_width;
}

float game_character::get_sprite_height()
{
    return sprite_height;
}

float game_character::get_bounding_rect_x()
{
    return dest_rec.x;
}

float game_character::get_bounding_rect_y()
{
    return dest_rec.y;
}

float& game_character::get_bounding_rect_ref_x()
{
    return dest_rec.x;
}

float& game_character::get_bounding_rect_ref_y()
{
    return dest_rec.y;
}

// Unloader(s)
void game_character::unload_character()
{
    UnloadTexture(char_texture);
}

// Destructor
game_character::~game_character()
{
    unload_character();
}


