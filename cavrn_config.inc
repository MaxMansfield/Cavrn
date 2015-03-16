SRC_NAME   := cavrn
LIBNAME    := lib$(SRC_NAME).a
ARCH       := $(shell uname -m)
SUPPORTED  := atmega103 atmega328p

# Add the current folders and files into the compile base
SOURCE_    := src
BUILD_     := build
INFO       := for $(DEVICE) on $(ARCH)
SRC_DIR   := $(addprefix $(SOURCE_)/,$(MODULES))
BUILD_DIR := $(addprefix $(BUILD_)/,$(MODULES))
CSRC      := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
HSRC      := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.h))
SRC       := $(CSRC) $(HSRC)
OBJ       := $(patsubst $(SOURCE_)%.c,$(BUILD_)%.o,$(CSRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR)) -I$(SOURCE_)


### Location of the examples folder relative to root
EXMPL_DIR    := examples

### Location of root folder relative to an example
EXMPL_DEPTH  := ../../../../

### Different folders of examples
EXMPL_TYPES  := Tx Rx

### Location of the example template relative to root
EXMPL_TEMPLT := $(EXMPL_DIR)/.__template

### Location of the example main source file relative to the root dir
EXMPL_SRC  := .__source
EXMPL_SOURCE  := $(EXMPL_DIR)/$(EXMPL_SRC)

### Include dirs, library dirs and definitions
DEFS	:= F_CPU=$(F_OSC) $(CE_PIN_DEF) $(CE_DDR_DEF) BAUD=$(BAUD)

### Soft-Programmer
AVRDUDE := avrdude -c arduino -p ${DEVICE} -P ${PORT} -b 115200 -U flash:w:$(MAIN).hex
RESET   := avrdude -c arduino -p ${DEVICE} -P ${PORT} -b 115200

### Optimization level (0, 1, 2, 3, 4 or s)
OPTIMIZE := s

### C Standard level (c89, gnu89, c99 or gnu99)
CSTD := c99

### Warning contorls
WARNINGS := all extra

# Output file format 
OUTPUT	:= ihex

### Programs to build project
CC      := avr-gcc
LD      := avr-ar
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
SIZE    := avr-size
MAKE    := make
NM      := avr-nm

# Flags for C files
CFLAGS += -fdata-sections -ffunction-sections -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
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


LDFLAGS := rcs
OCFLAGS := -R .eeprom -O $(OUTPUT)

