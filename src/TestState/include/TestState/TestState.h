#ifndef TESTSTATE_H_
#define TESTSTATE_H_

#include <GameState.h>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>

#include <sdl2class/Font.h>
#include <sdl2class/Texture.h>

namespace mtkaalund {
    class TestState : public mtkaalund::GameState {
        private:
            sdl2class::Texture *    m_image;
            sdl2class::Texture      m_text;

            sdl2class::Font         m_font;

            int                     m_x_travel;
        public:
            void init_state();
            void renderer();
            void handle_event();
            void update();
    };
}

#endif