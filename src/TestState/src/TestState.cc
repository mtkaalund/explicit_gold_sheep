#include <TestState/TestState.h>

namespace mtkaalund {

void TestState::init_state() {
    this->m_images["UI_red"].set_renderer( this->p_renderer );
    this->m_images["UI_green"].set_renderer( this->p_renderer );
    this->m_images["UI_blue"].set_renderer( this->p_renderer );
    this->m_images["UI_grey"].set_renderer( this->p_renderer );
    this->m_images["UI_yellow"].set_renderer( this->p_renderer );

    this->m_images["UI_red"].load("res/UI/Spritesheet/redSheet.png");
    this->m_images["UI_green"].load( "res/UI/Spritesheet/greenSheet.png");
    this->m_images["UI_blue"].load( "res/UI/Spritesheet/blueSheet.png");
    this->m_images["UI_grey"].load( "res/UI/Spritesheet/greySheet.png");
    this->m_images["UI_yellow"].load( "res/UI/Spritesheet/yellowSheet.png");

    this->m_img_text["UI_red"].set_renderer( this->p_renderer );
    this->m_img_text["UI_green"].set_renderer( this->p_renderer );
    this->m_img_text["UI_blue"].set_renderer( this->p_renderer );
    this->m_img_text["UI_grey"].set_renderer( this->p_renderer );
    this->m_img_text["UI_yellow"].set_renderer( this->p_renderer );

    this->sprites["UI_red"] = mtkaalund::load_from_json("res/UI/Spritesheet/redSheet.json");
    this->sprites["UI_green"] = mtkaalund::load_from_json("res/UI/Spritesheet/greenSheet.json");
    this->sprites["UI_blue"] = mtkaalund::load_from_json("res/UI/Spritesheet/blueSheet.json");
    this->sprites["UI_grey"] = mtkaalund::load_from_json("res/UI/Spritesheet/greySheet.json");
    this->sprites["UI_yellow"] = mtkaalund::load_from_json("res/UI/Spritesheet/yellowSheet.json");

    red_iterator = this->sprites["UI_red"].begin();
    green_iterator = this->sprites["UI_green"].begin();
    blue_iterator = this->sprites["UI_blue"].begin();
    grey_iterator = this->sprites["UI_grey"].begin();
    yellow_iterator = this->sprites["UI_yellow"].begin();

    this->m_images["UI_red"].set_clip( &red_iterator->second );
    this->m_images["UI_green"].set_clip( &green_iterator->second );
    this->m_images["UI_blue"].set_clip( &blue_iterator->second );
    this->m_images["UI_grey"].set_clip( &grey_iterator->second );
    this->m_images["UI_yellow"].set_clip( &yellow_iterator->second );

    if( this->m_font.load( "res/UI/Font/kenvector_future.ttf", 30) == false ) {
        throw TTFException();
    }

    if( this->m_img_font.load( "res/UI/Font/kenvector_future_thin.ttf", 12 ) == false ) {
        throw TTFException();
    }

    //#2E4053
    SDL_Color fb_color = {0x2e, 0x40, 0x53, 0x0f};
    SDL_Surface * tmp = this->m_font.RenderText("UI TestState", sdl2class::SOLID, &fb_color);

    if( tmp == nullptr ) {
        throw TTFException();
    }

    this->m_text.set_renderer( this->p_renderer );
    this->m_text.load( tmp );

    this->m_img_text["UI_red"].load( m_img_font.RenderText( red_iterator->first, sdl2class::SOLID, &fb_color ) );
    this->m_img_text["UI_green"].load( m_img_font.RenderText( green_iterator->first, sdl2class::SOLID, &fb_color ) );
    this->m_img_text["UI_blue"].load( m_img_font.RenderText( blue_iterator->first, sdl2class::SOLID, &fb_color ) );
    this->m_img_text["UI_grey"].load( m_img_font.RenderText( grey_iterator->first, sdl2class::SOLID, &fb_color ) );
    this->m_img_text["UI_yellow"].load( m_img_font.RenderText( yellow_iterator->first, sdl2class::SOLID, &fb_color ) );

    this->get_window_size();

    std::cout << "Window width: " << p_window_width << " Window Height: " << p_window_height << std::endl;
}

void TestState::renderer() {
    SDL_RenderClear( this->p_renderer );
    SDL_SetRenderDrawColor( this->p_renderer, 0xf0, 0xf0, 0x0f, 0xff );

    int index = 50;
    for( auto itr = this->m_images.begin(); itr != this->m_images.end(); ++itr ) {
        itr->second.set_point(this->p_window_width / 2 - itr->second.get_current_width() / 2, index );
        itr->second.renderer();
        index += itr->second.get_current_height() + 5;
    }

    this->m_img_text["UI_red"].set_point( 5, 50 );
    this->m_img_text["UI_green"].set_point( 5, 70 );
    this->m_img_text["UI_blue"].set_point( 5, 90 );
    this->m_img_text["UI_grey"].set_point( 5, 110 );
    this->m_img_text["UI_yellow"].set_point( 5, 130 );

    this->m_img_text["UI_red"].renderer();
    this->m_img_text["UI_green"].renderer();
    this->m_img_text["UI_blue"].renderer();
    this->m_img_text["UI_grey"].renderer();
    this->m_img_text["UI_yellow"].renderer();

    this->m_text.set_point( 5, 0 );
    this->m_text.renderer();
    SDL_RenderPresent( this->p_renderer );
}

void TestState::handle_event() {
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
            case SDL_QUIT:
                std::cerr << "Force quit activated!" << std::endl;
                this->state_force_quit = true;
                this->state_finished = true;
                break;
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ) {
                    case SDLK_ESCAPE:
                        std::cout << "Soft quit activated" << std::endl;
                        this->state_finished = true; // Soft quit
                        break;
                    case SDLK_SPACE:
                        this->red_iterator++;
                        this->green_iterator++;
                        this->blue_iterator++;
                        this->grey_iterator++;
                        this->yellow_iterator++;

                        if( this->red_iterator == this->sprites["UI_red"].end() ) {
                            this->red_iterator = this->sprites["UI_red"].begin();
                        }
                        if( this->green_iterator == this->sprites["UI_green"].end() ) {
                            this->green_iterator = this->sprites["UI_green"].begin();
                        }
                        if( this->blue_iterator == this->sprites["UI_blue"].end() ) {
                            this->blue_iterator = this->sprites["UI_blue"].begin();
                        }
                        if( this->grey_iterator == this->sprites["UI_grey"].end() ) {
                            this->grey_iterator = this->sprites["UI_grey"].begin();
                        }
                        if( this->yellow_iterator == this->sprites["UI_yellow"].end() ) {
                            this->yellow_iterator = this->sprites["UI_yellow"].begin();
                        }

                        this->m_images["UI_red"].set_clip( &this->red_iterator->second );
                        this->m_images["UI_green"].set_clip( &this->green_iterator->second );
                        this->m_images["UI_blue"].set_clip( &this->blue_iterator->second );
                        this->m_images["UI_grey"].set_clip( &this->grey_iterator->second );
                        this->m_images["UI_yellow"].set_clip( &this->yellow_iterator->second );

                        SDL_Color fb_color = {0x2e, 0x40, 0x53, 0x0f};

                        this->m_img_text["UI_red"].load( m_img_font.RenderText( red_iterator->first, sdl2class::SOLID, &fb_color ) );
                        this->m_img_text["UI_green"].load( m_img_font.RenderText( green_iterator->first, sdl2class::SOLID, &fb_color ) );
                        this->m_img_text["UI_blue"].load( m_img_font.RenderText( blue_iterator->first, sdl2class::SOLID, &fb_color ) );
                        this->m_img_text["UI_grey"].load( m_img_font.RenderText( grey_iterator->first, sdl2class::SOLID, &fb_color ) );
                        this->m_img_text["UI_yellow"].load( m_img_font.RenderText( yellow_iterator->first, sdl2class::SOLID, &fb_color ) );

                        break;
                }
                break;
        }
    }
}

void TestState::update() {
    //this->m_x_travel += this->m_x_direction;

   // SDL_Delay(10);

   // if( this->m_x_travel >= this->p_window_width ) {
   //     this->m_x_direction = -1;
   // } else if( this->m_x_travel <= 0 ) {
   //     this->m_x_direction = 1;
   // }
}

}