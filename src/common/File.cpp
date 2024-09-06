#include "../../inc/common/File.hpp"

std::string changeExtensionToO(const std::string &filename)
{
    // Find the last occurrence of '.'
    size_t lastDot = filename.find_last_of(".");

    // If there is no dot, append .o, otherwise replace the extension with .o
    if (lastDot == std::string::npos)
    {
        return filename + ".o";
    }
    else
    {
        return filename.substr(0, lastDot) + ".o";
    }
}