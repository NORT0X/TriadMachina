#pragma once

#include "File.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <fstream>

typedef uint32_t StringIndex; // Index inside Literal table;

typedef uint32_t SectionIndex;

typedef uint32_t SymbolIndex;

typedef uint32_t ForwardRefIndex;

/* Used by pareser */
enum
{
    SP = 14,
    PC = 15
};

enum
{
    STATUS = 0,
    HANDLER,
    CAUSE
};

/* -------------- */

enum SymbolBind
{
    LOCAL_BIND,
    GLOBAL_BIND,
    EXTERN_BIND
};

/* Table Entries */

struct LiteralEntry
{
    StringIndex index;
    std::size_t address;
    std::size_t offset;
    std::string literal;

    LiteralEntry(StringIndex index, std::size_t address, std::size_t offset, std::string literal)
        : index(index), address(address), offset(offset), literal(literal)
    {
    }
};

struct SymbolEntry
{
    SymbolIndex index;
    StringIndex name; // index inside literal table (pool)
    SectionIndex section_id;
    SymbolBind bind;
    uint32_t value;
    bool defined;
    ForwardRefIndex flink;

    SymbolEntry(SymbolIndex index, StringIndex name, SectionIndex section_id, SymbolBind bind, uint32_t value)
        : index(index), name(name), section_id(section_id), bind(bind), value(value)
    {
    }
};

struct SectionEntry
{
    SectionIndex index;
    StringIndex name;
    std::size_t base;
    std::size_t size;

    SectionEntry(SectionIndex index, StringIndex name, std::size_t base, std::size_t size)
        : index(index), name(name), base(base), size(size)
    {
    }
};

struct ForwardRefEntry
{
    ForwardRefIndex index;
    uint32_t patch;

    ForwardRefEntry(ForwardRefIndex index, uint32_t patch)
        : index(index), patch(patch)
    {
    }
};

class ElfFile : public File
{
public:
    bool open(const std::string &filename) override;
    void close() override;
    std::vector<char> read() override;
    bool write(const std::vector<char> &data) override;

private:
    std::fstream fileStream;
};
