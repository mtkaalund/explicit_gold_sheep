#ifndef _UTIL_H_
#define _UTIL_H_

#include <fstream>
#include <string>
#include <vector>

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

}

#endif