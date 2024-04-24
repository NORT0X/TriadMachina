
SOURCE_FILES = \
misc/flex.cpp \
misc/parser.cpp \
src/assembler/main.cpp

HEADER_FILES = \
inc/common/Elf.hpp \
misc/flex.hpp \
misc/parser.hpp

CXX=g++
OPT=-03

all: $(SOURCE_FILES) $(HEADER_FILES)
	$(CXX) $(SOURCE_FILES) -LFL -o assembly

