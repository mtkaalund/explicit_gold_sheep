#include <SplashState/SplashState.h>

namespace mtkaalund {

void SplashState::init_state() {
    this->m_image = new sdl2class::Texture( this->p_renderer, "res/images/Tux.png" );
    this->m_x_travel = 0;

    this->m_image_2.set_renderer( this->p_renderer );

    int _window_width, _window_height;
    SDL_GetWindowSize( this->p_window, &_window_width, &_window_height );

    if( this->m_image_2.create_blank( _window_width, _window_height, SDL_TEXTUREACCESS_TARGET ) == false ) {
        throw IMGException( "Failed to create target Texture" );
    }
}

void SplashState::renderer() {
    int _window_width, _window_height;
    SDL_GetWindowSize( this->p_window, &_window_width, &_window_height );

    this->m_image_2.set_as_render_target();

    SDL_SetRenderDrawColor( this->p_renderer, 0xff, 0xff, 0xff, 0xff );
    SDL_RenderClear( this->p_renderer );

    SDL_Rect fill_rect = { _window_width/4, _window_height/2, _window_width/2, _window_height/2 };
    SDL_SetRenderDrawColor( this->p_renderer, 0xff, 0x00, 0x00, 0xff );
    SDL_RenderFillRect( this->p_renderer, &fill_rect );

    SDL_SetRenderTarget( this->p_renderer, nullptr );
    SDL_RenderClear( this->p_renderer );

    this->m_image->set_point( this->m_x_travel, _window_height/2 - this->m_image->get_current_height()/2 );
    this->m_image->renderer();

    this->m_image_2.set_point( _window_width/2, _window_height/2);
    this->m_image_2.renderer();
    SDL_RenderPresent( this->p_renderer );

    SDL_Delay(10);

    if( this->m_x_travel >= _window_width ) {
        this->state_finished = true;
    }
}

void SplashState::handle_event() {

}

void SplashState::update() {
    this->m_x_travel += 1;
}

}