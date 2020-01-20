#ifndef GAMEOBJECT_TERRAIN_H_
#define GAMEOBJECT_TERRAIN_H_

//#include <GameObject/TerrainConfig.h>
// SDL2Core
#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
// SDL2class
#include <sdl2class/Texture.h>
// STD C++
#include <memory> // std::shared_ptr

namespace GameObject {

class Terrain
{
public:
    Terrain( int movement_cost, 
             bool is_water, 
             sdl2class::Texture texture ) 
             : movement_cost_( movement_cost ), 
               is_water_( is_water ), 
               texture_( texture )
    {}
    int get_movement_cost() const { return this->movement_cost_; }
    bool is_water() const { return this->is_water_; }
    const sdl2class::Texture& get_texture() const { return texture_ ; }
private:
  int movement_cost_;
  bool is_water_;
  sdl2class::Texture texture_;
};

}

#endif