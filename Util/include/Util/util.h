#ifndef _UTIL_H_
#define _UTIL_H_

#include <fstream>
#include <string>
#include <vector>

#include <map>
#include <list>
#include <sstream>
#include <exception>
#include <algorithm>

#include <sdl2core/SDL2.h>
#include <sdl2core/IMG.h>
#include <nlohmann/json.hpp>

#ifdef __linux__
    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/stat.h>
#elif _WIN32
    #include <windows.h>
#endif

namespace mtkaalund {

bool if_file_exists( std::string file_path );

// Taken from http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
void read_directory( const std::string& name, std::vector<std::string>& v );
bool create_directory( const std::string& name, bool create_parent);

// for loading from a json file
typedef std::map<std::string, SDL_Rect> map_of_rect;

map_of_rect load_from_json( std::string filename );

template<typename T>
bool contains( std::list<T> & listOfElements, const T & element )
{
    //Find the iterator if element in list
    auto it = std::find( listOfElements.begin(), listOfElements.end(), element );
    // Return if iterator points to end or not. It points to end the it means the element
    // does not exists in list
    return it != listOfElements.end();
}

}

#endif