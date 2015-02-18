ARCH       := $(shell uname -m)
BUILD_     := build
SOURCE_    := src
LIBNAME    := libcavrn.a

# Create the folder hierarchy for the example folders
CREATE_EXMPLS      := $(foreach mod,$(MODULES),$(shell mkdir -p examples/$(mod)/{Tx,Rx}))

### TX Examples
COPY_TEMPLATE    := $(foreach mod,$(MODULES),$(shell cp -r examples/.__template/* examples/$(mod)/Tx/))
### RX Examples
COPY_TEMPLATE    :=  $(foreach mod,$(MODULES),$(shell cp -r examples/.__template/* examples/$(mod)/Rx/))

# Add the current folders and files into the compile base
SRC_DIR   := $(addprefix $(SOURCE_)/,$(MODULES))
BUILD_DIR := $(addprefix $(BUILD_)/,$(MODULES))
CSRC      := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst $(SOURCE_)%.c,$(BUILD_)%.o,$(CSRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))
INCLUDES  += -I$(SOURCE_)

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
NM      := avr-nm

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
LDFLAGS += rcs

OCFLAGS := -R .eeprom -O $(OUTPUT)
