#include "../../inc/common/Elf.hpp"

#include <iostream>

bool ElfFile::open(const std::string &filename)
{
    fileStream.open(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    if (!fileStream)
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    return true;
}

void ElfFile::close()
{
    if (fileStream.is_open())
    {
        fileStream.close();
    }
}

std::vector<char> ElfFile::read()
{
    if (fileStream.is_open())
    {
        fileStream.seekg(0, std::ios::end);
        size_t size = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        fileStream.read(buffer.data(), size);

        return buffer;
    }
    else
    {
        std::cerr << "File not open for reading" << std::endl;
        return {};
    }
}

bool ElfFile::write(const std::vector<char> &data)
{
    if (fileStream.is_open())
    {
        fileStream.write(data.data(), data.size());
        return true;
    }

    std::cerr << "File not open for writing" << std::endl;
    return false;
}

bool ElfFile::writeAtPosition(size_t position, const std::vector<char> &data)
{
    if (fileStream.is_open())
    {
        // Move to the specified position and write data
        fileStream.seekp(position, std::ios::beg);
        if (fileStream.tellp() != static_cast<std::streampos>(position))
        {
            std::cerr << "Failed to seek to position: " << position << std::endl;
            return false;
        }

        fileStream.write(data.data(), data.size());
        if (!fileStream)
        {
            std::cerr << "Failed to write data at position: " << position << std::endl;
            return false;
        }

        // Move to the end of the file after writing
        fileStream.seekp(0, std::ios::end);

        return true;
    }

    std::cerr << "File not open for writing" << std::endl;
    return false;
}
