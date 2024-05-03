#include <cstdint>
#include <string>

class Assembler {
public:
    Assembler(std::string outputFile) : outputFile(outputFile) {}

private:
    uint32_t locationCounter = 0;

    std::string outputFile;

};
