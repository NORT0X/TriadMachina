
SOURCE_FILES = \
misc/flex.cpp \
misc/parser.cpp \
src/assembler/main.cpp \
src/common/Elf.cpp \
src/common/LiteralTable.cpp \
src/common/SectionTable.cpp \
src/common/SymbolTable.cpp \
src/common/RelaTable.cpp \
src/common/File.cpp \
src/assembler/Assembler.cpp \
src/assembler/AsBackpatch.cpp \
src/assembler/AsLoadStore.cpp

HEADER_FILES = \
inc/common/Elf.hpp \
inc/common/File.hpp \
inc/common/ForwardRefTable.hpp \
inc/common/LiteralTable.hpp \
inc/common/SectionTable.hpp \
inc/common/SymbolTable.hpp \
inc/common/RelaTable.hpp \
inc/assembler/Assembler.hpp \
misc/flex.hpp \
misc/parser.hpp

CXX=g++
OPT=-03
CXXFLAGS=-std=c++14 -static-libstdc++ --static

all: $(SOURCE_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(SOURCE_FILES) -LFL -o assembly.exe

