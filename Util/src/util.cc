#include <Util/util.h>

bool if_file_exists( std::string file_path )
{
	return static_cast<bool>(std::ifstream(file_path));
}

void read_directory( const std::string& name, std::vector<std::string>& v ) 
{
	#ifdef __linux__ 
	DIR * dirp = opendir( name.c_str() );
	struct dirent * dp;
	while( ( dp = readdir(dirp) ) != nullptr ) {
		v.push_back(dp->d_name);
	}
	closedir( dirp );

	#elif _WIN32

	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;

	if( (hFind = FindFirstFile( pattern.c_str(), &data)) != INVALID_HANDLE_VALUE ) {
		do {
			v.push_back( data.cFileName );
		} while( FindNextFile( hFind, &data ) != 0 );
		FindClose( hFind );
	}

	#endif
}


bool create_directory( const std::string& name, bool create_parent)
{
	#ifdef __linux__

	if( create_parent == true ) {
		size_t size = name.find_last_of('/');
		std::string p_name = name.substr(0, size);
		DIR * dirp = opendir( p_name.c_str() );
		if( dirp == nullptr ) {
			closedir(dirp);
			create_directory( p_name, true );
		}
		closedir(dirp);
		
	}

	const int dir_err = mkdir( name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	if( dir_err == -1 ) {
		return false;
	}
	#endif
	return true;
}
