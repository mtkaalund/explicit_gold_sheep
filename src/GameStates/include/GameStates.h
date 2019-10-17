#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <sdl2core/libSDL2.h>
#include <sdl2core/IMG.h>
#include <nlohmann/json.hpp>

class GameState {
public:
    virtual void init_state() {};
    virtual void handle_event() {};
    virtual void update() {};
    virtual void renderer() {};

    bool state_finished;
    SDL_Window      * p_window      = nullptr;
    SDL_Renderer    * p_renderer    = nullptr;

    // We need some way of getting a configuration and a save file.
};

#endif