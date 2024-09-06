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

typedef uint32_t Address;

#define HEADER_SIZE 32 // bytes

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

enum class LiteralMode // Used for LD and ST instructions
{
    VALUE,
    MEMORY
};

enum class SymbolMode // Used for LD and ST instructions
{
    VALUE,
    MEMORY
};

enum RegMode // Used for LD and ST instructions
{
    REG_DIR,
    REG_IND
};

enum SymbolBind
{
    LOCAL_BIND,
    GLOBAL_BIND,
    EXTERN_BIND,
    UND
};

enum class OPCODE
{
    HALT = 0,
    INT,
    CALL,
    JMP,
    XCHG,
    ARITHMETIC,
    LOGIC,
    SHIFT,
    STORE,
    LOAD
};

struct MInstruction
{
    OPCODE OC;
    uint8_t MOD;
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint32_t DISP;

    MInstruction() {}

    MInstruction(OPCODE OC, uint8_t MOD, uint8_t A, uint8_t B, uint8_t C, uint16_t DISP)
        : OC(OC), MOD(MOD), A(A), B(B), C(C), DISP(DISP)
    {
    }
};

struct ObjectHeader
{
    uint32_t codeStart;
    uint32_t codeSize;

    uint32_t symStart;
    uint32_t symSize;

    uint32_t secStart;
    uint32_t secSize;

    uint32_t relaStart;
    uint32_t relaSize;
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
    ABS,
    PC_REL
};

struct RelaEntry
{
    uint32_t offset;
    SectionIndex section_id;
    RelaType type;
    SymbolIndex symbol_id;
    int32_t addend;

    RelaEntry(uint32_t offset, SectionIndex section_id, RelaType type, SymbolIndex symbol_id, int32_t addend)
        : offset(offset), section_id(section_id), type(type), symbol_id(symbol_id), addend(addend)
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

    bool openForRead(const std::string &filename);

    bool writeAtPosition(size_t position, const std::vector<char> &data);
    bool readAtPosition(size_t position, std::vector<char> &data, size_t size);

    bool writeAtPosition(size_t position, uint32_t number);
    bool readAtPosition(size_t position, uint32_t &number);

    std::size_t getFileSize();

private:
    std::fstream fileStream;
};
