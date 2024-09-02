
COMMON_SOURCE_FILES = \
src/common/Elf.cpp \
src/common/LiteralTable.cpp \
src/common/SectionTable.cpp \
src/common/SymbolTable.cpp \
src/common/RelaTable.cpp \
src/common/File.cpp \

COMMON_HEADER_FILES = \
inc/common/Elf.hpp \
inc/common/File.hpp \
inc/common/ForwardRefTable.hpp \
inc/common/LiteralTable.hpp \
inc/common/SectionTable.hpp \
inc/common/SymbolTable.hpp \
inc/common/RelaTable.hpp


AS_SOURCE_FILES = \
misc/flex.cpp \
misc/parser.cpp \
src/assembler/main.cpp \
src/assembler/Assembler.cpp \
src/assembler/AsBackpatch.cpp \
src/assembler/AsLoadStore.cpp

AS_HEADER_FILES = \
inc/assembler/Assembler.hpp \
misc/flex.hpp \
misc/parser.hpp

LINKER_SOURCE_FILES = \
src/linker/main.cpp \
src/linker/Linker.cpp \
src/linker/Object.cpp

LINKER_HEADER_FILES = \
inc/linker/Linker.hpp \
inc/linker/Object.hpp

EMULATOR_SOURCE_FILES = \
src/emulator/main.cpp \
src/emulator/Bus.cpp \
src/emulator/CPU.cpp \
src/emulator/Emulator.cpp \
src/emulator/Instruction.cpp \
src/emulator/IO.cpp \
src/emulator/Memory.cpp

EMULATOR_HEADER_FILES = \
inc/emulator/Bus.hpp \
inc/emulator/CPU.hpp \
inc/emulator/Emulator.hpp \
inc/emulator/Instruction.hpp \
inc/emulator/IO.hpp \
inc/emulator/Memory.hpp

CXX=g++
OPT=-03

INCLUDE_PATHS = -Iinc -Imisc -Iinc/common -Iinc/assembler -Iinc/linker -Iinc/emulator
CXXFLAGS = -std=c++17 -static-libstdc++ --static $(INCLUDE_PATHS)


all: asembler linker emulator

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

asembler: $(AS_SOURCE_FILES:.cpp=.o) $(COMMON_SOURCE_FILES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(AS_SOURCE_FILES:.cpp=.o) $(COMMON_SOURCE_FILES:.cpp=.o) -o asembler.exe

linker: $(LINKER_SOURCE_FILES:.cpp=.o) $(COMMON_SOURCE_FILES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(LINKER_SOURCE_FILES:.cpp=.o) $(COMMON_SOURCE_FILES:.cpp=.o) -o linker.exe

emulator: $(EMULATOR_SOURCE_FILES:.cpp=.o) $(COMMON_SOURCE_FILES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(EMULATOR_SOURCE_FILES:.cpp=.o) $(COMMON_SOURCE_FILES:.cpp=.o) -o emulator.exe

	
clean:
	rm emulator.exe linker.exe asembler.exe
