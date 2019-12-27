#include <ResourceHandler/ResourceHandler.h>

namespace mtkaalund {

void ResourceHandler::get_resource_tree( const fs::path& path, int level )
{
    if( fs::exists( path ) && fs::is_directory( path ) )
    {
        auto lead = std::string( level * 3, ' ' );

        for( const auto& entry : fs::directory_iterator( path ) )
        {
            auto filename = entry.path().filename();
            if( fs::is_directory( entry.status() ) ) 
            {
                get_resource_tree( entry, level + 1 );
            } else if( fs::is_regular_file( entry.status() ) )
            {
                std::string ext = std::string(filename.extension().c_str());
                std::size_t pos = std::string(entry.path().c_str()).find("UI");
                if( ( pos != std::string::npos ) && pos != 0 ) {
                    std::cout << "UI found at " << pos << " '" << entry.path().c_str() << "'" << std::endl;
                }

                if( mtkaalund::contains( mtkaalund::audio, ext ) ) {
                    this->m_resources[AUDIO].push_back( entry );
                }

                if( mtkaalund::contains( mtkaalund::image, ext) ) {
                    this->m_resources[mtkaalund::IMAGE].push_back( entry );
                }

                if( mtkaalund::contains( mtkaalund::font, ext ) ) {
                    this->m_resources[mtkaalund::FONT].push_back( entry );
                }
            } else 
            {
                SDL_LogInfo(SDL_LOG_PRIORITY_INFO, "Unknown file: %s", filename.c_str() );
            }
        }
    }
}

void ResourceHandler::DisplayFileInfo( const fs::directory_entry &entry, std::string &lead, fs::path &filename )
{
    std::time_t cftime = std::chrono::system_clock::to_time_t(fs::last_write_time(entry));
    std::cout << lead << " " << filename << ", " << ComputeFileSize( entry ) << ", time: " << std::asctime( std::localtime( & cftime));
}

std::uintmax_t ResourceHandler::ComputeFileSize(const fs::path& pathToCheck)
{
	if (fs::exists(pathToCheck) && fs::is_regular_file(pathToCheck))
	{
		auto err = std::error_code{};
		auto filesize = fs::file_size(pathToCheck, err);
		if (filesize != static_cast<uintmax_t>(-1))
			return filesize;
	}

	return static_cast<uintmax_t>(-1);
}

void ResourceHandler::print_resource()
{
    for( auto item : this->m_resources ) {
        if( item.first == mtkaalund::FONT ) {
            std::cout << "FONT" << std::endl;
        }

        if( item.first == mtkaalund::IMAGE ) {
            std::cout << "IMAGE" << std::endl;
        }

        if( item.first == mtkaalund::AUDIO ) {
            std::cout << "AUDIO" << std::endl;
        }

        std::string old_pa = "";
        std::string parent_dir = "";        
        for( auto elem : item.second ) {
            std::cout << "\t" << elem << std::endl;
  //          if( elem.parent_path().parent_path().stem() == "Characters" ) {
//                parent_dir = std::string(elem.parent_path().stem()) + std::string(elem.parent_path().extension());
  //
//                if( old_pa != parent_dir )
//                    std::cout << "\t" << parent_dir << std::endl;
//                std::cout << "\t\t" << elem.filename().stem() << std::endl;
//                old_pa = parent_dir;
 //           }
        }
    }
}

std::vector<fs::path> &ResourceHandler::operator[](res_type id)
{
    if( id < NO_MORE_TYPE ) {
        return this->m_resources[ id ];
    }
}

};