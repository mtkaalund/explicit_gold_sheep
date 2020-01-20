#include <TileState/TileState.h>

namespace mtkaalund {

bool check_collision( SDL_Rect a, SDL_Rect b )
{
    // Getting the sides of the regtangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;
    // Calculate the sides of rect a
    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;
    // Calculate the sides of rect b
    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    if( bottom_a <= top_b ) return false;
    if( top_a >= bottom_b ) return false;
    if( right_a <= left_b ) return false;
    if( left_a >= right_b ) return false;

    return true;
}

void TileState::init_state() {

    this->load_landscape();

    SDL_SetWindowSize(this->p_window, 800, 600);
    this->p_window_height = 600;
    this->p_window_width = 800;

    if( this->m_font.load( "res/UI/Font/kenvector_future.ttf", 30) == false ) {
        throw TTFException();
    }

    if( this->m_screenFont.load( "res/UI/Font/kenvector_future.ttf", 12) == false ) {
        throw TTFException();
    }

    if( this->m_tile_font.load( "res/UI/Font/kenvector_future.ttf", 20) == false ) {
        throw TTFException();
    }

    //#2E4053
    this->fb_color = {0x2e, 0x40, 0x53, 0x0f};
    SDL_Surface * tmp = this->m_font.RenderText("MTKaalund", sdl2class::SOLID, &this->fb_color);

    if( tmp == nullptr ) {
        throw TTFException();
    }

    this->m_text.set_renderer( this->p_renderer );
    this->m_text.load( tmp );

//    this->m_tile_num.set_renderer( this->p_renderer );
//    this->m_num_of.set_renderer( this->p_renderer );

    //#2E4053
    SDL_Surface * tmp2 = this->m_screenFont.RenderText("testing", sdl2class::SOLID, &this->fb_color);

    if( tmp2 == nullptr ) {
        throw TTFException();
    }

    this->m_screenText.set_renderer( this->p_renderer );
    this->m_screenText.load( tmp2 );

    this->m_x_travel = 0;

    this->get_window_size();

    this->camera_rect.x = 0;
    this->camera_rect.y = 30;
    this->camera_rect.w = this->p_window_width;
    this->camera_rect.h = this->p_window_height - 30 - 53;

    this->view_rect.x   = 0;
    this->view_rect.y   = 30;
    this->view_rect.w   = ( this->p_window_width / mtkaalund::tile_width ) * mtkaalund::tile_width;
    this->view_rect.h   = ( ( this->p_window_height - 30 - 53 ) / mtkaalund::tile_height ) * mtkaalund::tile_height;

    for( int i = 0; i < mtkaalund::tile_map_width / mtkaalund::tile_width; i++)
    {
        for(int j = 0; j < mtkaalund::tile_map_height / mtkaalund::tile_height; j++ ) 
        {
            this->m_map_tile[i][j] = 0;
        }
    }

    std::cout << "view:\n\tx: " << this->view_rect.x << "\n\ty: " << this->view_rect.y << "\n\tw: " << this->view_rect.w << "\n\th: " << this->view_rect.h << std::endl;
    std::cout << "Window width: " << p_window_width << " Window Height: " << p_window_height << std::endl;
}

void TileState::renderer() {
    SDL_SetRenderDrawColor( this->p_renderer, 0xff, 0xff, 0xff, 0xff );
    SDL_RenderClear( this->p_renderer );

//    SDL_SetRenderDrawColor( this->p_renderer, 0xff, 0x00, 0x00, 0xff );    
//    for( int i = this->view_rect.x; i <= this->view_rect.w; i += mtkaalund::tile_width ){
//        SDL_RenderDrawLine( this->p_renderer, i, 30, i, this->view_rect.h + this->view_rect.y);
//    }

//    SDL_SetRenderDrawColor( this->p_renderer, 0x00, 0x00, 0xff, 0xff );
//    for( int i = this->view_rect.y; i <= this->view_rect.h+this->view_rect.y; i += mtkaalund::tile_height ){
//        SDL_RenderDrawLine( this->p_renderer, 0, i, this->view_rect.w, i);
//    }

    for( int x = this->camera_rect.x / mtkaalund::tile_width; x <= (this->camera_rect.x + this->camera_rect.w ) / mtkaalund::tile_width; x++ ) {
        for( int y = this->camera_rect.y / mtkaalund::tile_height; y <= (this->camera_rect.y + this->camera_rect.h) / mtkaalund::tile_height; y++ ) {
                int min_x = this->camera_rect.x / mtkaalund::tile_width;
                int min_y = this->camera_rect.y / mtkaalund::tile_height;

                int iso_x = ( x - y ) * mtkaalund::tile_width_half;
                int iso_y = ( x + y ) * mtkaalund::tile_height_half;

                SDL_Point screen_point = this->map_to_screen( { x , y } );
                SDL_Point pixel_point = this->screen_to_map( { screen_point.x, screen_point.y } );

                SDL_Point tmp_iso = this->Cartesian_to_Isometric({x,y});
                std::cout << "New implementation of isometric: { " << tmp_iso.x << " , " << tmp_iso.y  << "} ";
                std::cout << "Old: { " << pixel_point.x << " , " << pixel_point.y << " } " << std::endl;

//                std::cout << "screen_point: "
//                          << "\n x: " << screen_point.x
//                          << "\n y: " << screen_point.y
//                          << std::endl;
//                std::cout << "pixel_point: "
//                          << "\n x: " << pixel_point.x
//                          << "\n y: " << pixel_point.y
//                          << std::endl;


 //               std::cout << "camera_rect = {\n" 
//                          << "\tx: " << camera_rect.x
//                          << "\ty: " << camera_rect.y
//                          << "\tw: " << camera_rect.w
//                          << "\th: " << camera_rect.h 
//                          << std::endl;

//                std::cout << "min_x: " << min_x << std::endl;
//                std::cout << "min_y: " << min_y << std::endl;

                if( ( ( (x - min_x) >= view_rect.x/mtkaalund::tile_width ) && ( (x - min_x) < view_rect.w/mtkaalund::tile_width ) ) && ( (y-min_y) >= view_rect.y/mtkaalund::tile_height ) && ( (y-min_y) < view_rect.h/mtkaalund::tile_height ) )
                {
//                    std::string test = "[" + std::to_string( x ) + "][" + std::to_string( y ) + "]";
//                    SDL_Surface * test_surface = this->m_tile_font.RenderText(test, sdl2class::SOLID, &this->fb_color );
//                    this->m_num_of.load( test_surface );
//                    this->m_num_of.set_point( (x - min_x) * mtkaalund::tile_width, (y - min_y)*mtkaalund::tile_height + 30 );
//                    this->m_num_of.renderer();

//                    std::string number = std::to_string( this->m_map_tile[x][y]);
//                    SDL_Surface * map_example = this->m_tile_font.RenderText(number, sdl2class::SOLID, &this->fb_color);

//                    this->m_tile_num.load(map_example);
//                    this->m_tile_num.set_point( ((x - min_x)*mtkaalund::tile_width) + mtkaalund::tile_width/2 - this->m_tile_num.get_current_width()/2, (((y - min_y) * mtkaalund::tile_height)+30) + mtkaalund::tile_height/2 - this->m_tile_num.get_current_height()/2) ;
//                    this->m_tile_num.renderer();

//                    this->landscapes[ this->m_map_tile[x][y] ]->set_point( (x - min_x) * mtkaalund::tile_width, (y - min_y)*mtkaalund::tile_height + 30 );
                    this->landscapes[ this->m_map_tile[x][y] ]->set_point( screen_point );
                    this->landscapes[ this->m_map_tile[x][y] ]->renderer();

//                    SDL_FreeSurface( map_example );                    
                }
        }
    }


    SDL_SetRenderDrawColor( this->p_renderer, 0xcf, 0xfc, 0xcc, 0xff );
    SDL_Rect bottom_fillRect = {
        0, this->p_window_height - 74,//60,//53,
        this->p_window_width, this->p_window_height
    };
    SDL_RenderFillRect(this->p_renderer, &bottom_fillRect);

    SDL_Rect top_fillRect = {
        0, 0,
        this->p_window_width, 30
    };
    SDL_RenderFillRect(this->p_renderer, &top_fillRect);

    this->m_screenText.set_point( 4, this->p_window_height - 53);
    this->m_screenText.renderer();

    this->m_text.set_point( 4, 0 );
    this->m_text.renderer();
    SDL_RenderPresent( this->p_renderer );
}

void TileState::register_with_inputhandler( sdl2class::InputHandler& handler ) {
    handler.register_event( SDL_QUIT, [this](SDL_Event const& event ) {
        this->state_force_quit = true;
        this->state_finished = true;
    });
    handler.register_event( SDL_KEYUP, [this]( SDL_Event const& event ) {
        switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
                this->state_finished = true;
                break;
            case SDLK_UP:
                this->camera_rect.y -= mtkaalund::tile_height;
                if( this->camera_rect.y < 0 )
                {
                    this->camera_rect.y = 30;
                }
                break;
            case SDLK_DOWN:
                this->camera_rect.y += mtkaalund::tile_height;
                if( this->camera_rect.y >= ( mtkaalund::tile_map_height - this->camera_rect.h) ) {
                    this->camera_rect.y = mtkaalund::tile_map_height - this->camera_rect.h;
                }
                break;
            case SDLK_LEFT:
                this->camera_rect.x -= mtkaalund::tile_width;
                if( this->camera_rect.x <= 0 ) {
                    this->camera_rect.x = 0;
                }
                break;
            case SDLK_RIGHT:
                this->camera_rect.x += mtkaalund::tile_width;
                if( this->camera_rect.x >= ( mtkaalund::tile_map_width - p_window_width / 2) ) {
                    this->camera_rect.y = mtkaalund::tile_map_width;// - p_window_width / 2;
                }
                break;
        }
    });
    handler.register_event( SDL_MOUSEMOTION, [this]( SDL_Event const& event){
        int mouse_tile_x = event.motion.x / mtkaalund::tile_width;
        int mouse_tile_y = ( event.motion.y - 30 - 53 ) / mtkaalund::tile_height;
//        std::cout << "Mouse motion:\n"
//                  << "\t(x,y) : (" << event.motion.x << "," << event.motion.y << ")\n"
//                  << "\t(tx1,ty1) : (" << mouse_tile_x << "," << mouse_tile_y << ")\n";

    });
    handler.register_event( SDL_MOUSEBUTTONDOWN, [this]( SDL_Event const& event){
        int mouse_x, mouse_y;
        SDL_GetMouseState( &mouse_x, &mouse_y );

        SDL_Point pixel_to_tile = screen_to_map( { mouse_x+this->camera_rect.x, mouse_y+this->camera_rect.y-30} ); 

        int min_tile_x = this->camera_rect.x / mtkaalund::tile_width;
        int min_tile_y = this->camera_rect.y / mtkaalund::tile_height;
        int max_tile_x = ( this->camera_rect.x + this->camera_rect.w ) / mtkaalund::tile_width;
        int max_tile_y = ( this->camera_rect.y + this->camera_rect.h - 30 ) / mtkaalund::tile_height;
        int tile_x     = ((mouse_x/mtkaalund::tile_width)*mtkaalund::tile_width + this->camera_rect.x)/mtkaalund::tile_width;
        int tile_y     = (((mouse_y - 30)/mtkaalund::tile_height)*mtkaalund::tile_height + this->camera_rect.y)/mtkaalund::tile_height;

        std::cout << "Mouse Button: " 
                  << "\n\ttile_x: " << tile_x
                  << "\n\ttile_y: " << tile_y
                  << "\n\tpixel_to_tile.x: " << pixel_to_tile.x
                  << "\n\tpixel_to_tile.y: " << pixel_to_tile.y
                  << std::endl;
        tile_y = pixel_to_tile.y;
        tile_x = pixel_to_tile.x;
//        if( ( (tile_x >= min_tile_x) && (tile_x < max_tile_x) ) && ( ( tile_y >= min_tile_y ) && ( tile_y < max_tile_y ) ) )
//        {
            this->m_map_tile[tile_x][tile_y]++;
            if( this->m_map_tile[tile_x][tile_y] >= this->landscapes.size() ) 
            {
                this->m_map_tile[tile_x][tile_y] = 0;
            }
//        }
    });
}

void TileState::update() {
    SDL_Delay(10);
}

void TileState::load_landscape()
{
    auto read_path = mtkaalund::FileSystem::read_files_in_path("res/images/PNG/");

    for( auto entry : read_path ) {
        if( entry.extension() == ".png" ) {
            std::shared_ptr<sdl2class::Texture> tmp = std::make_shared<sdl2class::Texture>();
            tmp->set_renderer( this->p_renderer );
            tmp->load( entry.c_str() );
            this->landscapes.push_back( tmp );
        }
    }
}

SDL_Point TileState::map_to_screen( SDL_Point map_coordinates )
{
    SDL_Point tmp;

    tmp.x = ( map_coordinates.x - map_coordinates.y ) * mtkaalund::tile_width_half;
    tmp.y = ( map_coordinates.x + map_coordinates.y ) * mtkaalund::tile_height_half;

    return tmp;
}

SDL_Point TileState::screen_to_map( SDL_Point screen_pixels )
{
    SDL_Point tmp;

    tmp.x = ( screen_pixels.x / mtkaalund::tile_width_half + screen_pixels.y / mtkaalund::tile_height_half ) / 2;
    tmp.y = ( screen_pixels.y / mtkaalund::tile_height_half - screen_pixels.x / mtkaalund::tile_width_half ) / 2;

    return tmp;
}

SDL_Point TileState::Cartesian_to_Isometric( SDL_Point cartesian )
{
    SDL_Point tmp;
    tmp.x = cartesian.x - cartesian.y;
    tmp.y = ( cartesian.x + cartesian.y ) / 2;
    return tmp;
}

SDL_Point TileState::Isometric_to_Cartesian( SDL_Point isometric )
{
    SDL_Point tmp;
    tmp.x = (2 * isometric.y + isometric.x ) / 2;
    tmp.y = (2 * isometric.y - isometric.x ) / 2;
    return tmp;
}

}