#include <sdl2class/Texture.h>

namespace sdl2class {

Texture::Texture() {
    this->_rect     = nullptr; // { 0, 0, 0, 0 };
    this->_clip     = nullptr;
    this->_renderer = nullptr;
    this->_texture  = nullptr;
    this->_center   = nullptr;
    this->_pixels   = nullptr;
    this->_flip     = SDL_FLIP_NONE;
    this->_angle    = 0.0;
    this->_pitch    = 0;
}

Texture::Texture( SDL_Renderer * renderer ) {
    this->_clip     = nullptr;
    this->_renderer = nullptr;
    this->_texture  = nullptr;
    this->_rect     = nullptr; //{ 0, 0, 0, 0 };
    this->_center   = nullptr;
    this->_pixels   = nullptr;
    this->_flip     = SDL_FLIP_NONE;
    this->_angle    = 0.0;
    this->_pitch    = 0;
    this->set_renderer( renderer );
}
    
Texture::Texture( SDL_Renderer * renderer, std::string filename ) {
    this->_clip     = nullptr;
    this->_renderer = nullptr;
    this->_texture  = nullptr;
    this->_rect     = nullptr; //{ 0, 0, 0, 0 };
    this->_center   = nullptr;
    this->_pixels   = nullptr;
    this->_flip     = SDL_FLIP_NONE;
    this->_angle    = 0.0;
    this->_pitch    = 0;
    this->set_renderer( renderer );
    this->load( filename );
}

Texture::~Texture() {
    this->clear_texture();

    //if( this->_renderer != nullptr ) {
    //    this->_renderer = nullptr; //???
    //}
}

void Texture::clear_texture() {
    if( this->_texture != nullptr ) {
        SDL_DestroyTexture( this->_texture );
        this->_texture = nullptr;
        this->_clip     = nullptr;
        this->_rect     = nullptr;
        this->_center   = nullptr;
        this->_pixels   = nullptr;
        this->_flip     = SDL_FLIP_NONE;
        this->_angle    = 0.0;
        this->_pitch    = 0;
    }
}

bool Texture::create_blank(int width, int height, SDL_TextureAccess access) {
    this->clear_texture();
    // Create uninitialized texture
    this->_texture = SDL_CreateTexture( this->_renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );

//    std::cerr << "texture::create_blank : this->_texture = nullptr ? " << ( this->_texture == nullptr ? "true" : "false") << std::endl;

    if( this->_texture == nullptr ) {
        throw IMGException("Could not create blank texture");
        return false;
    }

    SDL_Rect tmp_clip = {0,0, width, height };
    this->_clip = &tmp_clip;

    return true;
}

void Texture::set_as_render_target() {
    // Make this is as renderer target
    if( ( this->_renderer != nullptr ) && ( this->_texture != nullptr ) ) {
        SDL_SetRenderTarget( this->_renderer, this->_texture );
    } else {
        if( this->_renderer == nullptr && this->_texture == nullptr ) {
            throw IMGException("Renderer & Texture is nullptr");
        }
        if( this->_renderer == nullptr ) {
            throw IMGException("Renderer is nullptr");
        }
        if( this->_texture == nullptr ) {
            throw IMGException("Texture is nullptr");
        }
    }
}

void Texture::set_renderer( SDL_Renderer * renderer ) {
    this->_renderer = renderer;
}

void Texture::set_alpha( char alpha ) {
    SDL_SetTextureAlphaMod( this->_texture, alpha );
}

void Texture::set_color( int red, int green, int blue ) {
    SDL_SetTextureColorMod( this->_texture, red, green, blue );
}

void Texture::set_clip( SDL_Rect * clip ) {
    this->_clip = clip;
    this->_rect->w = this->_clip->w;
    this->_rect->h = this->_clip->h;
}

void Texture::set_clip( int x, int y, int w, int h ) {
    SDL_Rect tmp_clip = { x, y, w, h };
    this->_clip = &tmp_clip;
    this->_rect->w = this->_clip->w;
    this->_rect->h = this->_clip->h;
}

void Texture::set_point( int x, int y ) {
    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
    }
    this->_rect->x = x;
    this->_rect->y = y;
}

void Texture::set_point( SDL_Point point ) {
    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
    }
    this->_rect->x = point.x;
    this->_rect->y = point.y;
}

void Texture::set_point_to_point( int x0, int y0, int x1, int y1 ) {
    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
    }

    this->_rect->x = x0;
    this->_rect->y = y0;
    if( x0 > x1 )
        this->_rect->w = x0 - x1;
    else
        this->_rect->w = x1 - x0;

    if( y0 > y1 )
        this->_rect->h = y0 - y1;
    else
        this->_rect->h = y1 - y0;
    std::cout << "_rect = {" << _rect->x << ", " << _rect->y << ", " << _rect->h << ", " << _rect->w << "}" << std::endl;
}

void Texture::set_rotate( double angle, SDL_Point * center ){
    this->_angle = angle;
    this->_center = center;
}

void Texture::flip( SDL_RendererFlip flip ) {
    this->_flip = flip;
}

bool Texture::lock_texture() {
    bool success = true;

    // if it is already locked
    if( ( this->_pixels == nullptr ) == false ) {
        std::cerr << "Texture is already locked!" << std::endl;
        success = false;
    } else {
        if( SDL_LockTexture( this->_texture, nullptr, &this->_pixels, &this->_pitch) != 0 ) {
            throw IMGException();
            success = false;
        }
    }

    return success;
}

bool Texture::unlock_texture() {
    bool success = true;

    if( this->_pixels == nullptr ) {
        std::cerr << "Texture is already not locked!" << std::endl;
        success = false;
    } else {
        SDL_UnlockTexture( this->_texture );
        this->_pixels = nullptr;
        this->_pitch = 0;
    }

    return success;
}
void * Texture::get_pixel() {
    return this->_pixels;
}

void Texture::copy_pixel( void * pixels ) {
    if( this->_pixels != nullptr ) {
        memcpy( this->_pixels, pixels, this->_pitch * this->_rect->h );
    }
}

int  Texture::get_pitch() {
    return this->_pitch;
}

uint32_t Texture::get_pixel32( unsigned int x, unsigned int y ) {
    // Convert the pixels to  32 bit
    uint32_t * pixels = ( uint32_t *) this->_pixels;
    // Get the pixels requested
    return pixels[ ( y * ( this->_pitch / 4) ) + x ];
}

void Texture::load( std::string filename ) {
    this->clear_texture();

    SDL_Surface * tmpSurface = IMG_Load( filename.c_str() );

    if( tmpSurface != nullptr && this->_renderer != nullptr ) {
        this->_texture = SDL_CreateTextureFromSurface( this->_renderer, tmpSurface );

        if( this->_texture == nullptr ) {
            throw IMGException("Failed to create texture from surface");
        }
    } else {
        throw IMGException();
    }

    SDL_FreeSurface(tmpSurface);
    tmpSurface = nullptr;

    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
        this->_rect->w = 0;
        this->_rect->h = 0;
        this->_rect->x = 0;
        this->_rect->y = 0;
    }

    if( this->_rect->h == 0 ) {
        this->_rect->h = this->get_original_height();
    }

    if( this->_rect->w == 0 ) {
        this->_rect->w = this->get_original_width();
    }
}

void Texture::load( SDL_Surface * _surface )
{
    this->clear_texture();

    if( _surface != nullptr && this->_renderer != nullptr ) {
        this->_texture = SDL_CreateTextureFromSurface( this->_renderer, _surface );

        if( this->_texture == nullptr ) {
            throw IMGException("Failed to create texture from surface");
        }
    } else {
        throw IMGException();
    }

    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
        this->_rect->w = 0;
        this->_rect->h = 0;
        this->_rect->x = 0;
        this->_rect->y = 0;
    }

    if( this->_rect->h == 0 ) {
        this->_rect->h = this->get_original_height();
    }

    if( this->_rect->w == 0 ) {
        this->_rect->w = this->get_original_width();
    }
}

void Texture::renderer() {
//    if( this->_clip != nullptr ) {
//        this->_rect->w = this->_clip->w;
//        this->_rect->h = this->_clip->h;
//    }
    
    SDL_RenderCopyEx( this->_renderer, this->_texture, this->_clip, this->_rect, this->_angle, this->_center, this->_flip);
}

bool Texture::is_loaded() {
    return ( this->_texture != nullptr ? true : false );
}

void Texture::scale( float value ) {
    this->scale_x( value );
    this->scale_y( value );
}

void Texture::scale_x( float value ) {
    int width;
    SDL_QueryTexture( this->_texture, nullptr, nullptr, &width, nullptr );
    float new_width = width * value;

    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
        this->_rect->w = 0;
        this->_rect->h = 0;
        this->_rect->x = 0;
        this->_rect->y = 0;
    }

    this->_rect->w = (int) new_width;    
}

void Texture::scale_y( float value ) {
    int height;
    SDL_QueryTexture( this->_texture, nullptr, nullptr, nullptr, &height );
    float new_height = height * value;

    if( this->_rect == nullptr ) {
        this->_rect = new SDL_Rect;
        this->_rect->w = 0;
        this->_rect->h = 0;
        this->_rect->x = 0;
        this->_rect->y = 0;
    }

    this->_rect->h = (int) new_height;
}

int Texture::get_original_width() {
    int w;
    SDL_QueryTexture( this->_texture, nullptr, nullptr, &w, nullptr );
    return w;
}

int Texture::get_original_height() {
    int h;
    SDL_QueryTexture( this->_texture, nullptr, nullptr, nullptr, &h );
    return h;
}

int Texture::get_current_width() {
    return this->_rect->w;
}

int Texture::get_current_height() {
    return this->_rect->h;
}

}