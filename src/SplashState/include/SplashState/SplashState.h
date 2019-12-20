#ifndef SPLASHSTATE_H_
#define SPLASHSTATE_H_

#include <GameState.h>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>

#include <sdl2class/Font.h>
#include <sdl2class/Texture.h>
#include <sdl2class/InputHandler.h>

namespace mtkaalund {
    class SplashState : public mtkaalund::GameState {
        private:
            sdl2class::Texture *    m_image;
            sdl2class::Texture      m_text;

            sdl2class::Font         m_font;

            int                     m_x_travel;
        public:
            void init_state();
            void renderer();
            void register_with_inputhandler( sdl2class::InputHandler& handler );
            void update();
    };
}

#endif