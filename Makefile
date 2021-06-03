#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------
TARGET := caddie
BUILD_DIR := build
EXTERNALS_DIR := externals

CPP_FILES := $(wildcard src/*.cpp)
LDSCRIPT := $(BUILD_DIR)/ldscript.lcf

# Outputs
MAP     := $(BUILD_DIR)/$(TARGET).map
O_FILES := $(CPP_FILES:.c=.o)

include obj_files.mk

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------
# Programs
CC    := tools/mwcceppc
LD    := tools/mwldeppc
KAMEK := tools/Kamek

# Options
LDFLAGS := -map $(MAP) -mapunused -proc gekko -fp hard -nodefaults -nofail
CFLAGS  := -i . -I- -i include -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0
KFLAGS  := $(O_FILES) -externals=$(EXTERNALS_DIR)/ntscu.txt -output-kamek=$(BUILD_DIR)/caddieUS.bin

SRC_DIRS := game core \
	game/golf

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------
default: all

clean:
	rm -fdr build

all:
	ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS))
	# Make sure build directory exists before compiling anything
	DUMMY != mkdir -p $(ALL_DIRS)

	$(BUILD_DIR)/%.o: %.cpp
		$(warning TEST2)
		$(CC) $(CFLAGS) -c -o $@ $<