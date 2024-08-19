
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

CXX=g++
OPT=-03
CXXFLAGS=-std=c++14 -static-libstdc++ --static

asembler: $(COMMON_SOURCE_FILES) $(COMMON_HEADER_FILES) $(AS_SOURCE_FILES) $(AS_HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(AS_SOURCE_FILES) $(COMMON_SOURCE_FILES) -LFL -o asembler.exe

linker: $(COMMON_SOURCE_FILES) $(COMMON_HEADER_FILES) $(LINKER_SOURCE_FILES) $(LINKER_HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(LINKER_SOURCE_FILES) $(COMMON_SOURCE_FILES) -LFL -o linker.exe

