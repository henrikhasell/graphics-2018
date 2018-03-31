#include "path.hpp"

std::string remove_filename(const char *file_path)
{
    std::string full_path = file_path;
    size_t index = full_path.rfind('/');
    return index == std::string::npos ? "./" : full_path.substr(0, index + 1);
}