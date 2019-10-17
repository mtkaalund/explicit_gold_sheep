#ifndef SPLASHSTATE_H_
#define SPLASHSTATE_H_

#include <GameState.h>
#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
#include <sdl2class/Texture.h>

namespace mtkaalund {
    class SplashState : public mtkaalund::GameState {
        private:
            sdl2class::Texture *    m_image;
            sdl2class::Texture      m_image_2;

            int                     m_x_travel;
        public:
            void init_state();
            void renderer();
            void handle_event();
            void update();
    };
}

#endif