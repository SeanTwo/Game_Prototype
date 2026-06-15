#include <raylib.h>
#include <string>
#include <array>
#include "game_window.h"
#include "direction.h"
#include "sprite_matrix.h"

class entity
{
    private:
        Rectangle source_rec;
        Rectangle dest_rec;
        Vector2 origin;
        sprite_matrix current_spritesheet_pos; // the current position of the spritesheet being used for animation
        float sprite_width; // width of a single frame in the spritesheet in pixels
        float sprite_height; // height of a single frame in the spritesheet in pixels
        float rotation;
        int chara_id;
        float x;
        float y;
        float world_grid_size;
        Texture2D char_texture;

        void set_spritesheet_pos(float x, float y);
        void normalize_coordinates();

    public:
        // Constructors
        entity(
            std::string texture_path,
            Vector2 initial_position,
            const window_config& screen,
            std::array<float, 2> sprite_scale,
            int chara_id,
            int width_pixels,
            int height_pixels,
            int world_grid_size
        );

        // Class Functions
        void draw();

        void rotate();

        void set_rotation(float rotation_angle);

        void move(direction dir, float speed, float dt);

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

        float get_rotation();

        float get_sprite_width();

        float get_sprite_height();

        float get_bounding_rect_x();

        float get_bounding_rect_y();

        float& get_bounding_rect_ref_x();

        float& get_bounding_rect_ref_y();

        // Unloader
        void unload_character();

        // Destructor
        ~entity();
};