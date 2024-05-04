
SOURCE_FILES = \
misc/flex.cpp \
misc/parser.cpp \
src/assembler/main.cpp \
src/common/LiteralTable.cpp \
src/common/SectionTable.cpp \
src/common/SymbolTable.cpp

HEADER_FILES = \
inc/common/Elf.hpp \
inc/common/ForwardRefTable.hpp \
inc/common/LiteralTable.hpp \
inc/common/SectionTable.hpp \
inc/common/SymbolTable.hpp \
misc/flex.hpp \
misc/parser.hpp

CXX=g++
OPT=-03

all: $(SOURCE_FILES) $(HEADER_FILES)
	$(CXX) $(SOURCE_FILES) -LFL -o assembly.exe

