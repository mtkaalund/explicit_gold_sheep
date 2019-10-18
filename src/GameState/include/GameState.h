#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
#include <nlohmann/json.hpp>

namespace mtkaalund {

class GameState {
public:
    virtual void init_state() {};
    virtual void handle_event() {};
    virtual void update() {};
    virtual void renderer() {};

    inline void get_window_size() {
        SDL_GetWindowSize( this->p_window, &p_window_width, &p_window_height );
    }

    bool state_finished;
    bool state_force_quit;
    SDL_Window      * p_window      = nullptr;
    SDL_Renderer    * p_renderer    = nullptr;

    int p_window_width;
    int p_window_height;

    // We need some way of getting a configuration and a save file.
    nlohmann::json    config;
    nlohmann::json    save;
};

}

#endif