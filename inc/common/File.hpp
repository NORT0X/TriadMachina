#pragma once

#include <string>
#include <vector>

class File
{
public:
    File() {}

    virtual bool open(const std::string &filename) = 0;
    virtual void close() = 0;
    virtual bool write(const std::vector<char> &data) = 0;
    virtual std::vector<char> read() = 0;
};