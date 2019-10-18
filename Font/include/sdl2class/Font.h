#ifndef SDL2CLASS_FONT_H_
#define SDL2CLASS_FONT_H_

#include <string>
#include <iostream>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
#include <sdl2core/TTF.h>

namespace sdl2class {

enum FONT_STYLE {
    SOLID,
    SHADED,
    BLENDED
};

class Font {
private:
    TTF_Font *      p_font;
    std::string     p_font_path;
    int             p_font_size;

public:
    Font();
    ~Font();

    bool load( std::string path, int size );
    SDL_Surface * RenderText( std::string text, FONT_STYLE style, SDL_Color * fb_color, SDL_Color * bg_color = nullptr);
};

}

#endif