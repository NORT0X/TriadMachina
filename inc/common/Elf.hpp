#pragma once

#include "File.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <fstream>

typedef uint32_t LiteralIndex;

typedef uint32_t StringIndex;

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
    LiteralIndex index;
    uint32_t value;
    std::string symbol;
    bool isSymbol;

    LiteralEntry(uint32_t value, bool isSymbol = false)
        : value(value), isSymbol(isSymbol) {}

    LiteralEntry(uint32_t value, std::string symbol, bool isSymbol = true)
        : value(value), isSymbol(isSymbol), symbol(symbol) {}
};

struct SymbolEntry
{
    SymbolIndex index;
    StringIndex name; // index inside symbol names table (pool)
    SectionIndex section_id;
    SymbolBind bind;
    uint32_t value;
    bool defined;
    ForwardRefIndex flink;

    SymbolEntry(StringIndex name, SectionIndex section_id, SymbolBind bind, uint32_t value, bool defined = false, ForwardRefIndex flink = -1)
        : name(name), section_id(section_id), bind(bind), value(value), defined(defined), flink(flink)
    {
    }
};

struct SectionEntry
{
    SectionIndex index;
    StringIndex name;
    std::size_t base;
    std::size_t size;

    SectionEntry(StringIndex name, std::size_t base, std::size_t size)
        : name(name), base(base), size(size)
    {
    }
};

struct ForwardRefEntry
{
    ForwardRefIndex index;
    uint32_t patch;
    ForwardRefIndex next; // It's like single linked list inside symbol entry

    ForwardRefEntry(ForwardRefIndex index, uint32_t patch, ForwardRefIndex next = -1)
        : index(index), patch(patch), next(next)
    {
    }
};

enum RelaType
{
    DIRECT,
    PC_REL
};

struct RelaEntry
{
    uint32_t offset;
    SectionIndex section_id;
    RelaType type;
    SymbolIndex symbol_id;
    uint32_t addend;
};

class ElfFile : public File
{
public:
    bool open(const std::string &filename) override;
    void close() override;
    std::vector<char> read() override;
    bool write(const std::vector<char> &data) override;

    bool writeAtPosition(size_t position, const std::vector<char> &data);

private:
    std::fstream fileStream;
};
