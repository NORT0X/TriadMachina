CXXFILES = flex.cpp parser.cpp

all: $(CXXFILES)

flex.cpp: flex.l 
	flex flex.l

parser.cpp: parser.y flex.l
	bison parser.y

clean:
	rm -rf *.o *.d flex.cpp flex.hpp parser.cpp parser.hpp
