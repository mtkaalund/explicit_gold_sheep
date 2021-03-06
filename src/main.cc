#include <exception>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>

#include <cstdlib> // getenv

#include <nlohmann/json.hpp>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
#include <sdl2core/TTF.h>
#include <sdl2core/MIX.h>

#include <sdl2class/InputHandler.h>

#include <Util/util.h>
#include <GameState.h>
#include <SplashState/SplashState.h>
#include <TestState/TestState.h>
#include <TileState/TileState.h>
#include <Arguments/Arguments.h>

#include <ResourceHandler/ResourceHandler.h>

int main( int argc, char * argv[] ) {
    Arguments argument;
//    mtkaalund::ResourceHandler * res_handler = new mtkaalund::ResourceHandler;

//    res_handler->get_resource_tree( "res/");
//    res_handler->print_resource();

//    std::vector<fs::path> image = (*res_handler)[mtkaalund::IMAGE];
//    for( auto item : image )
//    {
//        std::cout << item.c_str() << std::endl;
//    }

    nlohmann::json arg_cfg, config, env;

    // Getting enviroment variables
    env["HOME"] = getenv("HOME");
    env["USER"] = getenv("USER");
    env["LANG"] = getenv("LANG");
    env["PWD"]  = getenv("PWD");

    // Setting up the argument parser
    argument.set_argument("--screen", Arguments::string);
    argument.set_argument("--screen_width", Arguments::integer);
    argument.set_argument("--screen_height", Arguments::integer);
    argument.set_argument("--fullscreen", Arguments::boolean);
    argument.set_argument("--enable-cheat", Arguments::boolean);
    arg_cfg = argument.parse( argc, argv );

    // Create a config path string
    std::string config_path = env["HOME"].get<std::string>() + "/.tile_game/config.json";

    if( mtkaalund::if_file_exists( config_path ) == true ) {
        std::ifstream config_input( config_path );
        config_input >> config;
    } else {
        std::cerr << "Found no config at: " << config_path << std::endl;
        mtkaalund::create_directory( env["HOME"].get<std::string>() + "/.tile_game/saves", true );
        config["save_path"] = env["HOME"].get<std::string>() + "/.tile_game/saves/"; 
    }

    if( arg_cfg.size() > 0 ) {
        config.merge_patch( arg_cfg );
    }

    if( mtkaalund::if_file_exists( config_path ) == false ) {
        std::ofstream config_out( config_path );
        config_out << std::setw(4) << config << std::endl;
    } 

    std::cout << "Config:\n";
    std::cout << config.dump(4) << std::endl;

    std::cout << "Title Game with state pattern" << std::endl;

    try {
        SDL2 sdl2( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO );
        IMG  img( IMG_INIT_PNG | IMG_INIT_JPG );
        TTF  ttf;
//        MIX mix( MIX_INIT_MP3 | MIX_INIT_OGG );

        SDL_Window * m_window = nullptr;
        SDL_Renderer * m_renderer = nullptr;

        sdl2class::InputHandler m_inputhandler;

        // Set texture filtering to linear
        if( ! SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        std::list<mtkaalund::GameState *> game_states;

        game_states.push_back( new mtkaalund::TileState() );
//        game_states.push_back( new mtkaalund::SplashState() );
//        game_states.push_back( new mtkaalund::TestState() );

        m_window = SDL_CreateWindow( "TileGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN );

        if( m_window == nullptr ) {
            std::cerr << "Could not create window!" << std::endl;
            throw SDL2Exception();
        }

        m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( m_renderer == nullptr ) {
            std::cerr << "Could not create renderer!" << std::endl;
            throw SDL2Exception();
        }

        SDL_SetRenderDrawColor( m_renderer, 0xff, 0xff, 0xff, 0xff );

        while( game_states.size() > 0 ) {
            mtkaalund::GameState * state = game_states.front();
            game_states.pop_front();

            state->state_finished = false;
            state->state_force_quit = false;
            state->p_window = m_window;
            state->p_renderer = m_renderer;
            state->config = config;
            state->register_with_inputhandler( m_inputhandler );

            state->init_state();
            while( state->state_finished == false && state->state_force_quit == false ) {
                m_inputhandler.handle_events();

                if( state->state_force_quit == true ) {
                    break;
                }

                state->update();
                state->renderer();

//                state->state_finished = true;
            }

            config = state->config;

            if( state->state_force_quit == true ) {
                break;
            }
        }
        std::ofstream config_out( config_path );
        config_out << std::setw(4) << config << std::endl;

        SDL_DestroyRenderer( m_renderer );
        SDL_DestroyWindow( m_window );
    } catch( SDL2Exception &error ) {
        std::cerr << "SDL2 Error: " << error.what() << std::endl;
    } catch( IMGException &error ) {
        std::cerr << "IMG Error: " << error.what() << std::endl;
    } catch( TTFException &error ) {
        std::cerr << "TTF Error: " << error.what() << std::endl;
    } catch( MIXException &error ) {
        std::cerr << "MIX Error: " << error.what() << std::endl;
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "MIX Error: %s", error.what() );
    } catch( std::exception &error ) {
        std::cerr << "Generic error: " << error.what() << std::endl;
    }

    return 0;
} 