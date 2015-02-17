ARCH      := $(shell uname -m)

# Add the current folders and files into the compile base
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))
CSRC      := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst src/%.c,build/%.o,$(CSRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))
INCLUDES  += -Isrc/

### Include dirs, library dirs and definitions
DEFS	= F_CPU=$(F_OSC) $(CE_PIN_DEF) $(CE_DDR_DEF)
DEFS   += BAUD=$(BAUD)

### Optimization level (0, 1, 2, 3, 4 or s)
OPTIMIZE = s

### C Standard level (c89, gnu89, c99 or gnu99)
CSTD = c99

### Warning contorls
WARNINGS = all extra

### Output file format (ihex, bin or both) and debugger type
OUTPUT	= ihex
DEBUG	= # dwarf-2

### Programs to build porject
CC      = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size
NM      = avr-nm


PROJECT   := $(BUILD_DIR)/$(PROJECT)


# Flags for C files
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -Wno-deprecated-declarations -D__PROG_TYPES_COMPAT__
CFLAGS += -Wl,--gc-sections
CFLAGS += -Wall
CFLAGS += -std=$(CSTD)
CFLAGS += -g$(DEBUG)
CFLAGS += -mmcu=$(DEVICE)
CFLAGS += -O$(OPTIMIZE) -mcall-prologues
CFLAGS += $(addprefix -W,$(WARNINGS))
CFLAGS += $(INCLUDES)
CFLAGS += $(addprefix -D,$(DEFS))
CFLAGS += -Wp,-M,-MP,-MT,-MF

# Linker flags
LDFLAGS += -Wl,-lm -Wl,--gc-sections,-Map,$(PROJECT).map

vpath %.c $(SRC_DIR)