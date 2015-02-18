#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Makefile for the Cavrn AVR8 library                                         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Version: 1.0                                                                #
# Max Mansfield on February 17, 2015                                          #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
include settings.inc

ARCH       := $(shell uname -m)
BUILD_     := build
SOURCE_    := src
MAIN       := $(BUILD_)/$(MAIN_FILE)
# Add the current folders and files into the compile base
SRC_DIR   := $(addprefix $(SOURCE_)/,$(MODULES))
SRC_DIR   += $(SOURCE_)
BUILD_DIR := $(addprefix $(BUILD_)/,$(MODULES))
BUILD_DIR += $(BUILD_)
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
LD      := avr-gcc
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
LDFLAGS += -Wl,-lm -Wl,--gc-sections

OCFLAGS := -R .eeprom -O $(OUTPUT)

vpath %.c $(SRC_DIR) %o $(BUILD_DIR)

.PHONY: all makedirs success version upload console clean

all: version makedirs makeobjs $(MAIN).out $(MAIN).hex size success

$(BUILD_DIR):
	@mkdir -p $@

makedirs: $(BUILD_DIR)
makeobjs: $(OBJ)

$(OBJ): $(CSRC) 
	$(CC) -c $(CFLAGS) $< -o $@

$(MAIN).out: $(MAIN).o
	$(LD) $(LDFLAGS) $^ -o $@ 

$(MAIN).hex: $(MAIN).out
	$(OBJCOPY) $(OCFLAGS) $< $@


success: $(OBJ) $(BUILD_DIR) $(MAIN).hex
	@echo
	@echo
	@echo
	@echo Modules Built: $(MODULES)
	@echo Cavrn Build Success!

size: $(MAIN).out $(MAIN).hex
	$(SIZE)  -C --mcu=$(DEVICE) $(MAIN).out

version :
	@$(CC) --version

clean:
	@echo
	rm -f -r $(BUILD_DIR) build/

upload:
	@echo
	$(AVRDUDE) 

console:
	@echo
	$(AVRDUDE) 
	screen $(PORT) $(BAUD)





