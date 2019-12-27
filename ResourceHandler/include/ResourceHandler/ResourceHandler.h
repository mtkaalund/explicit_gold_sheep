#ifndef MTKAALUND_RESOURCEHANDLER_H_
#define MTKAALUND_RESOURCEHANDLER_H_
//! \file ResourceHandler.h
//!
//! 
#include <map>
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>

#if __GNUC__ > 8
    #include <filesystem>
    namespace fs = std::filesystem;
#else
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#endif

#include <Util/util.h>

namespace mtkaalund {

typedef enum {
    AUDIO,
    IMAGE,
    FONT,
    NO_MORE_TYPE
} res_type;

const std::vector<std::string> font = {
    ".ttf",
    ".fon"
};

const std::vector<std::string> audio = {
    ".wav",
    ".mp3",
    ".ogg",
    ".mod",
    ".midi"
};

const std::vector<std::string> image = {
    ".png",
    ".jpg",
    ".jpeg",
    ".ico",
    ".cur",
    ".bmp",
    ".pnm",
    ".ppm",
    ".pgm",
    ".pbm",
    ".xpm",
    ".lbm",
    ".iff",
    ".ilbm",
    ".pcx",
    ".gif",
    ".tga",
    ".tiff",
    ".tif"
};

class ResourceHandler {
private:
    std::map<res_type, std::vector<fs::path> > m_resources;
public:
    void get_resource_tree( const fs::path& path, int level = 0 );
    void DisplayFileInfo( const fs::directory_entry &entry, std::string &lead, fs::path &filename );
    std::uintmax_t ComputeFileSize(const fs::path& pathToCheck);

    // Testing a way to overload
    std::vector<fs::path> &operator[](res_type id);
    
    void print_resource();
};

}

#endif