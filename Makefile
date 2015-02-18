#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Makefile for the Cavrn AVR8 library                                         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Version: 1.1                                                                #
# Max Mansfield on February 18, 2015                                          #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
include settings.inc
include cavrn_config.inc

.PHONY: all dirs obj staticlib success version upload console clean
all: version dirs obj  success 

$(BUILD_DIR):  
	@mkdir -p $@
dirs: $(BUILD_DIR)

$(OBJ):
	@echo
	@echo [Creating Object File] $@ [compiling]
	@echo
	$(CC) $(CFLAGS) -c "$(SOURCE_)$(shell echo '$(@:.o=.c)'  | sed 's/$(BUILD_)//g')" -o $@
	@echo
	@echo [Object File Created] $@  [from] "$(SOURCE_)$(shell echo '$(@:.o=.c)'  | sed 's/$(BUILD_)//g')" [complete]
	@echo	
obj: $(OBJ)

$(LIBNAME): $(OBJ) $(CSRC)
	@echo
	@echo Creating static library...
	$(LD) $(LDFLAGS) $(BUILD_)/$(LIBNAME) $(OBJ) 
	@echo Created $(LIBNAME) static library
	@echo
staticlib: $(LIBNAME)

success: $(BUILD_DIR) $(OBJ) $(LIBNAME)
	@echo
	@echo
	@echo
	@echo Modules Built: $(MODULES)
	@echo Cavrn Build Success!

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






