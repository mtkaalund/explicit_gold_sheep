#include <mtkaalund/FileSystem.h>

namespace mtkaalund {
    namespace FileSystem {
std::vector<fs::path> read_files_in_path( const fs::path& path, int level )
{
    std::vector<fs::path> tmp;
    if( fs::exists( path ) && fs::is_directory( path ) )
    {
        for( const auto& entry : fs::directory_iterator( path ) )
        {
            if( fs::is_directory( entry.status() ) == true ) {
                auto fil = read_files_in_path( entry.path(), level+1 );
                tmp.reserve( tmp.size() + fil.size() );
                std::move( fil.begin(), fil.end(), std::back_inserter(tmp) );
            } else if( fs::is_regular_file( entry.status() ) == true ) {
                tmp.push_back( entry.path() );   
            }
        }
    }

    return tmp;
}


    }
}