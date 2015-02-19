#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Example Makefile for the Cavrn AVR8 library                                         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Version: 1.0                                                                #
# Max Mansfield on February 17, 2015                                          #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
include settings.inc
MAIN := $(MAIN_FILE:.c=)
DEPTH := ../../../
# Add the current folders and files into the compile base
SOURCE_    := cavrn
BUILD_     := $(EXMPL_DEPTH)build
SRC_DIR   := $(addprefix $(SOURCE_)/,$(MODULES))
BUILD_DIR := $(addprefix $(BUILD_)/,$(MODULES))
CSRC      := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
HSRC      := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.h))
SRC       := $(CSRC) $(HSRC)
OBJ       := $(patsubst $(SOURCE_)%.c,$(BUILD_)%.o,$(CSRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR)) -I$(SOURCE_)

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
CFLAGS += $(addprefix -D,$(DEFS))
CFLAGS += -Wp,-M,-MP,-MT,-MF

# Linker flags
LDFLAGS += -Wl,-lm -Wl,--gc-sections

OCFLAGS := -R .eeprom -O $(OUTPUT)

vpath %.c $(SRC_DIR) %o $(BUILD_DIR)

.PHONY: all makedirs success version upload console clean

all: version  $(MAIN).o $(MAIN).elf size

$(MAIN).o: $(MAIN).c 
	$(CC) -c $(CFLAGS)  $< -o $@
$(MAIN).elf: $(MAIN).o 
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEPTH)$(OBJ) $< -o $@
$(MAIN).hex: $(MAIN).elf
	$(OBJCOPY) -O ihex $< $@

size: $(MAIN).elf $(MAIN).hex
	$(SIZE)  -C --mcu=$(DEVICE) $(MAIN).elf

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





