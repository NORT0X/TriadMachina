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

bool ElfFile::openForRead(const std::string &filename)
{
    fileStream.open(filename, std::ios::binary | std::ios::in);
    if (!fileStream)
    {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
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

bool ElfFile::readAtPosition(size_t position, std::vector<char> &data, size_t size)
{
    if (fileStream.is_open())
    {
        // Move to the specified position and read data
        fileStream.seekg(position, std::ios::beg);
        if (fileStream.tellg() != static_cast<std::streampos>(position))
        {
            std::cerr << "Failed to seek to position: " << position << std::endl;
            return false;
        }

        data.resize(size);
        fileStream.read(data.data(), size);
        if (!fileStream)
        {
            std::cerr << "Failed to read data at position: " << position << std::endl;
            return false;
        }

        return true;
    }

    std::cerr << "File not open for reading" << std::endl;
    return false;
}

bool ElfFile::writeAtPosition(size_t position, uint32_t number)
{
    std::vector<char> buff(4, 0);

    buff[3] = number >> 8 * 3;
    buff[2] = number >> 8 * 2;
    buff[1] = number >> 8 * 1;
    buff[0] = number;

    return this->writeAtPosition(position, buff); // NOT RECURSION
}

bool ElfFile::readAtPosition(size_t position, uint32_t &number)
{
    if (fileStream.is_open())
    {
        // Move to the specified position
        fileStream.seekg(position, std::ios::beg);
        if (fileStream.tellg() != static_cast<std::streampos>(position))
        {
            std::cerr << "Failed to seek to position: " << position << std::endl;
            return false;
        }

        // Create a buffer to hold 4 bytes (size of uint32_t)
        std::vector<char> buffer(4);

        // Read 4 bytes from the file
        fileStream.read(buffer.data(), 4);
        if (!fileStream)
        {
            std::cerr << "Failed to read data at position: " << position << std::endl;
            return false;
        }

        // Convert the buffer into a uint32_t
        number = static_cast<uint32_t>(
            (static_cast<uint8_t>(buffer[3]) << 24) | // little-endian order
            (static_cast<uint8_t>(buffer[2]) << 16) |
            (static_cast<uint8_t>(buffer[1]) << 8) |
            (static_cast<uint8_t>(buffer[0])));

        return true;
    }

    std::cerr << "File not open for reading" << std::endl;
    return false;
}

std::size_t ElfFile::getFileSize()
{
    if (fileStream.is_open())
    {
        // Save the current position of the file pointer
        std::streampos currentPos = fileStream.tellg();

        // Seek to the end of the file
        fileStream.seekg(0, std::ios::end);

        // Get the position, which is the size of the file
        std::size_t fileSize = static_cast<std::size_t>(fileStream.tellg());

        // Restore the file pointer to its original position
        fileStream.seekg(currentPos);

        return fileSize;
    }
    else
    {
        std::cerr << "File not open to get size" << std::endl;
        return 0;
    }
}
