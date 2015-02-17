#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Makefile for the Cavrn AVR8 library                                         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Version: 1.0                                                                #
# Max Mansfield on February 17, 2015                                          #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
include settings.inc
include cavrn_config.inc

.PHONY: all makedirs success version upload console clean
all: version makedirs success 

$(BUILD_DIR):  
	@mkdir -p $@

$(OBJ): $(CSRC)
	$(CC) $(CFLAGS) -c $< -o  $@ 

makedirs: $(BUILD_DIR)

success: $(OBJ)
	@echo
	@echo
	@echo
	@echo Modules Built: $(MODULES)
	@echo Cavrn Build Success!

version :
	@$(CC) --version

clean:
	@echo
	rm -f -r $(BUILD_DIR) 

upload:
	@echo
	$(AVRDUDE) 

console:
	@echo
	$(AVRDUDE) 
	screen $(PORT) $(BAUD)





