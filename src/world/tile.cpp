#include "tile.h"

tile::tile(
    std::string texture_path,
    Vector2 position,
    const window_config& screen,
    int world_grid_size,
    sprite_matrix spritesheet_pos,
    std::array<float, 2> sprite_scale
)
{
    this->sprite_sheet = LoadTexture(texture_path.c_str());
    this->rotation = 0.0f;
    this->sprite_dim = (float)world_grid_size;
    set_spritesheet_frame(spritesheet_pos);
    this->source_rec = { 0.0f, 0.0f, sprite_dim, sprite_dim };
    this->dest_rec = { sprite_scale[0]*2+position.x, sprite_scale[1]*2+position.y, sprite_dim*sprite_scale[0], sprite_dim*sprite_scale[1] }; // Sets the initial position of the tile
    this->origin = { sprite_dim, sprite_dim };
}

tile::tile(
    std::string texture_path,
    Vector2 position,
    const window_config& screen,
    int world_grid_size,
    sprite_matrix spritesheet_pos,
    std::array<float, 2> sprite_scale,
    float rotation
)
{
    this->sprite_sheet = LoadTexture(texture_path.c_str());
    this->rotation = rotation;
    this->sprite_dim = (float)world_grid_size;
    set_spritesheet_frame(spritesheet_pos);
    this->source_rec = { 0.0f, 0.0f, sprite_dim, sprite_dim };
    this->dest_rec = { sprite_scale[0]*2+position.x, sprite_scale[1]*2+position.y, sprite_dim*sprite_scale[0], sprite_dim*sprite_scale[1] }; // Sets the initial position of the tile
    this->origin = { sprite_dim, sprite_dim };
}

 // Class Functions
void tile::draw()
{
    DrawTexturePro(sprite_sheet, source_rec, dest_rec, origin, rotation, WHITE);
}

void tile::set_rotation(float rotation_angle)
{
    this->rotation = rotation_angle;
}

void tile::set_pos(float x, float y)
{
    this->dest_rec.x = x;
    this->dest_rec.y = y;
}

void tile::set_spritesheet_frame(sprite_matrix sprite_pos)
{
    this->current_spritesheet_pos = sprite_pos;
    this->source_rec.x = this->sprite_dim * sprite_pos.col;
    this->source_rec.y = this->sprite_dim * sprite_pos.row;
}

// Getter Functions
sprite_matrix tile::get_spritesheet_pos()
{
    return this->current_spritesheet_pos;
}

int tile::get_spritesheet_row()
{
    return this->current_spritesheet_pos.row;
}

int tile::get_spritesheet_col()
{
    return this->current_spritesheet_pos.col;
}

float tile::get_x_coord()
{
    return this->dest_rec.x;
}

float tile::get_y_coord()
{
    return this->dest_rec.y;
}

// Getters for raylib based character attributes
Texture2D tile::get_texture()
{
    return this->sprite_sheet;
}

Rectangle tile::get_src_rect()
{
    return this->source_rec;
}

Rectangle tile::get_dest_rect()
{
    return this->dest_rec;
}

Vector2 tile::get_origin()
{
    return this->origin;
}

// Unloader(s)
void tile::unload_tile()
{
    UnloadTexture(sprite_sheet);
}

// Destructor
tile::~tile()
{
    unload_tile();
}
