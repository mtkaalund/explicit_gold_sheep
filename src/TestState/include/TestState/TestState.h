#ifndef TESTSTATE_H_
#define TESTSTATE_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include <GameState.h>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>

#include <sdl2class/Font.h>
#include <sdl2class/Texture.h>

#include <nlohmann/json.hpp>

namespace mtkaalund {

    typedef std::map<std::string, SDL_Rect> map_of_rect;

    class TestState : public mtkaalund::GameState {
        private:
            sdl2class::Texture *    m_image;
            sdl2class::Texture      m_text;

            sdl2class::Font         m_font;
            int                     m_x_travel;
            int                     m_x_direction;
            mtkaalund::map_of_rect  sprite;
            mtkaalund::map_of_rect::iterator sprite_iterator;

        public:
            void init_state();
            void renderer();
            void handle_event();
            void update();
    };
}

#endif