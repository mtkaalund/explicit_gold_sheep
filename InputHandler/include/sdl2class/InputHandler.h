#ifndef SDL2CLASS_INPUTHANDLER_H_
#define SDL2CLASS_INPUTHANDLER_H_


// this is from https://gamedev.stackexchange.com/a/89793

#include <sdl2core/SDL2.h>

#include <map>
#include <vector>
#include <functional>

namespace sdl2class {

using EventCallback = std::function< void( SDL_Event const& ) >;

class InputHandler {
private:
    std::map< SDL_EventType, std::vector< EventCallback > > _callbacks;
public:
    void register_event( SDL_EventType type, EventCallback callback ) {
        this->_callbacks[ type ].push_back( callback );
    }

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