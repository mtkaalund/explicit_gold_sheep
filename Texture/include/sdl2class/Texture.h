#ifndef SDL2CLASS_TEXTURE_H_
#define SDL2CLASS_TEXTURE_H_

#include <string>
#include <iostream>

#include <sdl2core/IMG.h>
#include <sdl2core/TTF.h>

namespace sdl2class {

class Texture {
protected:
    SDL_Rect     *  _rect;
    SDL_Rect     *  _clip;
    SDL_Renderer *  _renderer;
    SDL_Texture  *  _texture;
    SDL_Point    *  _center;

    SDL_RendererFlip  _flip;

    void         *  _pixels;
    int             _pitch;
    double          _angle;
public:
    Texture();
    Texture( SDL_Renderer * renderer );
    Texture( SDL_Renderer * renderer, std::string filename );
    // Destructor and clearing texture
    virtual ~Texture();
    void clear_texture();

    bool create_blank(int width, int height, SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING );

    void set_blend_mode( SDL_BlendMode blending );

    void set_as_render_target();
    void set_renderer( SDL_Renderer * renderer );

    void set_alpha( char alpha );
    void set_color( int red, int green, int blue );
    void set_clip( SDL_Rect * clip = nullptr );
    void set_clip( int x, int y, int w, int h );

    void set_point( int x, int y );
    void set_point( SDL_Point point );

    void set_point_to_point( int x0, int y0, int x1, int y1 );

    void set_rotate( double angle = 0.0, SDL_Point * center = nullptr );

    void flip( SDL_RendererFlip flip = SDL_FLIP_NONE );

    // Pixel maniplulation
    bool lock_texture();
    bool unlock_texture();
    void * get_pixel();
    void copy_pixel( void * pixels );
    int  get_pitch();
    uint32_t get_pixel32( unsigned int x, unsigned int y );

    void load( std::string filename );
    void load( SDL_Surface * _surface );
    void renderer();

    bool is_loaded();

    void scale( float value );
    void scale_x( float value );
    void scale_y( float value );

    int get_original_width();
    int get_original_height();

    int get_current_width();
    int get_current_height();
};

}

#endif