#ifndef TESTSTATE_H_
#define TESTSTATE_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include <GameState.h>

#include <Util/util.h>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>

#include <sdl2class/Font.h>
#include <sdl2class/Texture.h>
#include <sdl2class/InputHandler.h>

#include <nlohmann/json.hpp>

namespace mtkaalund {

    class TestState : public mtkaalund::GameState {
        private:
            std::map<std::string, sdl2class::Texture> m_images;
            sdl2class::Texture      m_text;
            sdl2class::Texture      m_panel;

            std::map<std::string, sdl2class::Texture> m_img_text;

            sdl2class::Font         m_font;
            sdl2class::Font         m_img_font;
            int                     m_x_travel;
            int                     m_x_direction;
            std::map<std::string, mtkaalund::map_of_rect> sprites;
            mtkaalund::map_of_rect::iterator sprite_iterator;
            mtkaalund::map_of_rect::iterator red_iterator;
            mtkaalund::map_of_rect::iterator green_iterator;
            mtkaalund::map_of_rect::iterator blue_iterator;
            mtkaalund::map_of_rect::iterator grey_iterator;
            mtkaalund::map_of_rect::iterator yellow_iterator;
            std::map<std::string, sdl2class::Texture>::iterator font_iterator;

        public:
            void init_state();
            void renderer();
            void register_with_inputhandler( sdl2class::InputHandler& handler );
            void update();
    };
}

#endif