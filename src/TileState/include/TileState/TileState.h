#ifndef TILESTATE_H_
#define TILESTATE_H_

#include <memory>
#include <vector>
#include <array>

#include <GameState.h>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>

#include <sdl2class/Font.h>
#include <sdl2class/Texture.h>
#include <sdl2class/InputHandler.h>

#include <mtkaalund/FileSystem.h>

#include <GameObject/Terrain.h>
#include <GameObject/TileEngine.h>

namespace mtkaalund {

    const int tile_width = 132;
    const int tile_width_half = tile_width / 2;
    const int tile_height = 99;
    const int tile_height_half = tile_height / 2;
    const int tile_map_width = tile_width * 100;
    const int tile_map_height = tile_height * 100;

    bool check_collision( SDL_Rect a, SDL_Rect b );

    class TileState : public mtkaalund::GameState {
        private:
            sdl2class::Texture      m_text;
            sdl2class::Texture      m_screenText;
//            sdl2class::Texture      m_tile_num;
//            sdl2class::Texture      m_num_of;

            sdl2class::Font         m_font;
            sdl2class::Font         m_screenFont;
            sdl2class::Font         m_tile_font;

            SDL_Color               fb_color;

            int                     m_x_travel;

            SDL_Rect                camera_rect;
            SDL_Rect                view_rect;
            std::array<std::array<int,mtkaalund::tile_map_width/mtkaalund::tile_width>,mtkaalund::tile_map_height/mtkaalund::tile_height > m_map_tile;
            std::vector<std::shared_ptr<sdl2class::Texture> > landscapes;

        public:
            void init_state();
            void renderer();
            void register_with_inputhandler( sdl2class::InputHandler& handler );
            void update();
            void load_landscape();
            SDL_Point map_to_screen( SDL_Point map_coordinates );
            SDL_Point screen_to_map( SDL_Point screen_pixels );
            SDL_Point Cartesian_to_Isometric( SDL_Point cartesian );
            SDL_Point Isometric_to_Cartesian( SDL_Point isometric );
    };
}

#endif