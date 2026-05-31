#include <raylib.h>
#include <string>
#include <array>
#include "game_window.h"
#include "direction.h"

class game_character
{
    private:
        Rectangle source_rec;
        Rectangle dest_rec;
        Vector2 origin;
        float frame_width;
        float frame_height;
        float rotation;
        int chara_id;
        Texture2D char_texture;
    public:
        // Constructors
        game_character(
            std::string texture_path,
            Vector2 initial_position,
            const window_config& screen,
            std::array<float, 2> frame_mult,
            int chara_id
        );

        // Class Functions
        void draw();

        void rotate();

        void set_rotation(float rotation_angle);

        void move(direction dir, float speed, float dt);

        void set_pos(float x, float y);

        // Getter Functions
        Texture2D get_texture();

        Rectangle get_src_rect();

        Rectangle get_dest_rect();

        Vector2 get_origin();

        float get_rotation();

        float get_texture_width();

        float get_texture_height();

        // Unloader
        void unload_character();
};