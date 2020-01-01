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
//! \fn std::vector<std::filesystem::path> read_files_in_path( const std::filesystem::path& path, int level = 0 )
//! This will return all files in the path, and subdirectories. But it will not contain the directories.
//! @param path Giv the start path, for reading the path.
//! @param level Starts at 0, but will increment as it goes in the subdirectories.
std::vector<fs::path> read_files_in_path( const fs::path& path, int level = 0 );

    }
}

#endif