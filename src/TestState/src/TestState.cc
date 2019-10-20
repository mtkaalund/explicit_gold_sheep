#include <TestState/TestState.h>

namespace mtkaalund {

void TestState::init_state() {
    this->m_image = new sdl2class::Texture( this->p_renderer, "res/UI/Spritesheet/blueSheet.png" );


    nlohmann::json spritesheet_json;
    std::ifstream file_input("res/UI/Spritesheet/blueSheet.json");
    file_input >> spritesheet_json;
    file_input.close();

    std::cout << std::setw(4) << spritesheet_json << std::endl;

    std::cout << std::setw(4) << spritesheet_json["TextureAtlas"]["SubTexture"] << std::endl;
    
    for(auto& element: spritesheet_json["TextureAtlas"]["SubTexture"]) {
        std::stringstream str_tmp;
        
        str_tmp << std::string(element["@height"]);
        str_tmp >> sprite[std::string( element["@name"] )].h;
        
        str_tmp.clear();
        str_tmp << std::string(element["@width"]);
        str_tmp >> sprite[std::string( element["@name"] )].w;

        str_tmp.clear();
        str_tmp << std::string(element["@x"]);
        str_tmp >> sprite[std::string( element["@name"] )].x;

        str_tmp.clear();
        str_tmp << std::string(element["@y"]);
        str_tmp >> sprite[std::string( element["@name"] )].y;
    }

    std::cout << "Size of sprite: " << sprite.size() << std::endl;

    sprite_iterator =  sprite.begin();
    this->m_image->set_clip( &sprite_iterator->second );

    if( this->m_font.load( "res/UI/Font/kenvector_future.ttf", 30) == false ) {
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


    this->m_x_travel = 0;
    this->m_x_direction = 1;

    this->get_window_size();

    std::cout << "Window width: " << p_window_width << " Window Height: " << p_window_height << std::endl;
}

void TestState::renderer() {
    SDL_RenderClear( this->p_renderer );
    SDL_SetRenderDrawColor( this->p_renderer, 0xff, 0xff, 0xff, 0xff );

    this->m_image->set_point( this->m_x_travel, p_window_height/2 - sprite_iterator->second.h/2 );
    this->m_image->renderer( );

    this->m_text.set_point( 0, 0 );
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
                        this->sprite_iterator++;
                        if( this->sprite_iterator == sprite.end() ) {
                            this->sprite_iterator = sprite.begin();
                        }
                        this->m_image->set_clip( &sprite_iterator->second );

                        break;
                }
                break;
        }
    }
}

void TestState::update() {
    this->m_x_travel += this->m_x_direction;

    SDL_Delay(10);

    if( this->m_x_travel >= this->p_window_width ) {
        this->m_x_direction = -1;
        //this->state_finished = true;
    } else if( this->m_x_travel <= 0 ) {
        this->m_x_direction = 1;
    }
}

}