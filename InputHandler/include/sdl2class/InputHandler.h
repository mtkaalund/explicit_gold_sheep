#ifndef SDL2CLASS_INPUTHANDLER_H_
#define SDL2CLASS_INPUTHANDLER_H_

//! \file InputHandler.h
//! \brief This class is not of my design.
//! Most of the class is taken from https://gamedev.stackexchange.com/a/89793 with
//! some alterations in order to not clash with C++ registered words.

#include <sdl2core/SDL2.h>

#include <map>
#include <vector>
#include <functional>

namespace sdl2class {

using EventCallback = std::function< void( SDL_Event const& ) >;

//! SDL Event input handler class
//! This class will save the sdl2 events into a std::map, which can be accessed later.
//! @code
//! class GameManager {
//! public:
//!
//!  void registerWithEventHandler(EventHandler& handler) {
//!    handler.register(SDL_KEYUP, [this](SDL_Event const& event){
//!      if (event.key.keysym.sym == SDLK_ESCAPE) {
//!        Quit();
//!      }
//!    });
//!    handler.register(SDL_QUIT, [this](SDL_Event const& event){
//!      Quit();
//!    });
//!  }
//!
//!};
//!@endcode
class InputHandler {
private:
    std::map< SDL_EventType, std::vector< EventCallback > > _callbacks; //!< Maps SDL_EventType to a std::vector of EventCallback
public:
    //! Registers events takes two arguments and puts it into a std::vector
    //! \param type is a SDL_EventType
    //! \param callback is a EventCallback
    void register_event( SDL_EventType type, EventCallback callback ) {
        this->_callbacks[ type ].push_back( callback );
    }
    //! Polls the events. In your code, run this once.
    void handle_events() {
        SDL_Event event;
        while( SDL_PollEvent( &event ) != 0 ) {
            for( auto& cb : this->_callbacks[ event.type ] ) {
                cb( event );
            }
        }
    }
};

}

#endif