#ifndef MTKAALUND_FILESYSTEM_H
#define MTKAALUND_FILESYSTEM_H
//! \file FileSystem.h
//!
//!
#if __GNUC__ > 8
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <algorithm>
#include <string>
#include <vector>

namespace mtkaalund {
    namespace FileSystem {

std::vector<fs::path> read_files_in_path( const fs::path& path, int level = 0 );

    }
}

#endif