#include <raylib.h>
#include <string>
#include <array>
#include "sprite_matrix.h"
#include "game_window.h"

class tile
{
    private:
        Rectangle source_rec;
        Rectangle dest_rec;
        Vector2 origin;
        sprite_matrix current_spritesheet_pos; // the current tile being used in the spritesheet
        float rotation;
        float sprite_dim; // width and height of a single tile in the spritesheet in pixels
        Texture2D* sprite_sheet; // the spritesheet texture for all tiles in the world

    public:
        // Constructors
        tile(
            Texture2D* sprite_sheet,
            int x,
            int y,
            const window_config& screen,
            int world_grid_size,
            sprite_matrix current_spritesheet_pos,
            std::array<float, 2> sprite_scale
        );

        tile(
            Texture2D* sprite_sheet,
            int x,
            int y,
            const window_config& screen,
            int world_grid_size,
            sprite_matrix current_spritesheet_pos,
            std::array<float, 2> sprite_scale,
            float rotation
        );

         // Class Functions
        void draw();

        void draw(Color color);

        void set_rotation(float rotation_angle);

        void set_pos(float x, float y);

        void set_spritesheet_frame(sprite_matrix sprite_pos);

        // Getter Functions
        sprite_matrix get_spritesheet_pos();

        int get_spritesheet_row();

        int get_spritesheet_col();

        float get_x_coord();

        float get_y_coord();

        // Getters for raylib based character attributes
        Texture2D get_texture();

        Rectangle get_src_rect();

        Rectangle get_dest_rect();

        Vector2 get_origin();
};