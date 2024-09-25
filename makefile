BUILD_TYPE ?= release

COMMON_SOURCE_FILES := $(wildcard src/common/*.cpp)
AS_SOURCE_FILES := $(wildcard misc/*.cpp src/assembler/*.cpp)
LINKER_SOURCE_FILES := $(wildcard src/linker/*.cpp)
EMULATOR_SOURCE_FILES := $(wildcard src/emulator/*.cpp)


# Compiler and Flags
CXX=g++
OPT=-O3

# Include Paths
INCLUDE_PATHS = -Iinc -Imisc -Iinc/common -Iinc/assembler -Iinc/linker -Iinc/emulator
ifeq ($(BUILD_TYPE), debug)
    CXXFLAGS = -std=c++17 -g -DDEBUG $(INCLUDE_PATHS)
else
    CXXFLAGS = -std=c++17 $(OPT) -static-libstdc++ --static $(INCLUDE_PATHS)
endif

# Output Directory
BUILD_DIR = build

# Subdirectories
SUBDIRS = $(BUILD_DIR)/misc $(BUILD_DIR)/src/assembler $(BUILD_DIR)/src/common $(BUILD_DIR)/src/linker $(BUILD_DIR)/src/emulator

# Targets
all: $(BUILD_DIR) $(SUBDIRS) assembler linker emulator

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(SUBDIRS):
	mkdir -p $(SUBDIRS)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

assembler: $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(AS_SOURCE_FILES)) $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(COMMON_SOURCE_FILES))
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/assembler $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(AS_SOURCE_FILES) $(COMMON_SOURCE_FILES))

linker: $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(LINKER_SOURCE_FILES)) $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(COMMON_SOURCE_FILES))
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/linker $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(LINKER_SOURCE_FILES) $(COMMON_SOURCE_FILES))

emulator: $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(EMULATOR_SOURCE_FILES)) $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(COMMON_SOURCE_FILES))
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/emulator $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(EMULATOR_SOURCE_FILES) $(COMMON_SOURCE_FILES))

clean:
	find . -type f -name '*.o' -not -path './test/*' -exec rm -f {} +
	rm -rf $(BUILD_DIR)

debug: BUILD_TYPE = debug
debug: all

