#ifndef GAMEOBJECT_TILEENGINE_H_
#define GAMEOBJECT_TILEENGINE_H_

#include <TileEngineConfig.h>
// SDL2Core
#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
// SDL2class
#include <sdl2class/Texture.h>
// GameObject
#include <GameObject/Terrain.h>
// STD C++
#include <memory> // std::shared_ptr
#include <vector> // std::vector

namespace GameObject {

class TileEngine
{
public:

private:
    // This is our object pool
    std::vector< std::shared_ptr< Texture > > tiles_;
};

}

#endif