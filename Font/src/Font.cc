#include <sdl2class/Font.h>

namespace sdl2class {

Font::Font() {
    p_font      = nullptr;
    p_font_size = 0;
    p_font_path.clear();
}

Font::~Font() {
    if( p_font != nullptr ) {
        TTF_CloseFont( p_font );
        p_font = nullptr;
    }

    p_font_size = 0;
    p_font_path.clear();
}

bool Font::load( std::string path, int size ) {
    p_font_path = path;
    p_font_size = size;

    p_font      = TTF_OpenFont( p_font_path.c_str(), p_font_size );

    return p_font != nullptr;
}

SDL_Surface * Font::RenderText( std::string text, FONT_STYLE style, SDL_Color * fb_color, SDL_Color * bg_color) {
    SDL_Surface * tmp = nullptr;
    SDL_Color fb, bg;

    if( fb_color == nullptr ) {
        fb = {0xff, 0xff, 0xff, 0xff };
    } else {
        fb = {fb_color->r, fb_color->g, fb_color->b, fb_color->r };
    }

    if( bg_color == nullptr ) {
        bg = {0xff, 0xff, 0xff, 0xff };
    } else {
        bg = {bg_color->r, bg_color->g, bg_color->b, bg_color->r };
    }

    switch( style ) {
        case SOLID:
            tmp = TTF_RenderText_Solid( this->p_font, text.c_str(), fb );
            break;
        case SHADED:
            tmp = TTF_RenderText_Shaded( this->p_font, text.c_str(), fb, bg );
            break;
        case BLENDED:
            tmp = TTF_RenderText_Blended( this->p_font, text.c_str(), fb );
            break;
    }

    return tmp;
}

}