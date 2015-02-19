#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Makefile for the Cavrn AVR8 library                                         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Version: 1.2                                                                #
# Max Mansfield on February 18, 2015                                          #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
include settings.inc         # settings of the build to be edited by the user
include cavrn_config.inc     # build configuration options that the user doesnt need to touch

.PHONY: all dirs obj staticlib success version upload console clean
all: version dirs obj success 

$(BUILD_DIR):  
	@mkdir -p $@
dirs: $(BUILD_DIR)

$(OBJ):
	@echo
	@echo [Creating Object File $(INFO) ] $@ [compiling]
	@echo
	$(CC) $(CFLAGS) -c "$(SOURCE_)$(shell echo '$(@:.o=.c)'  | sed 's/$(BUILD_)//g')" -o $@
	@echo
	@echo [Object File Created] $@  [from] "$(SOURCE_)$(shell echo '$(@:.o=.c)'  | sed 's/$(BUILD_)//g')" [complete]
	@echo	
obj: $(OBJ)

$(LIBNAME): $(OBJ) $(CSRC)
	@echo
	@echo
	$(LD) $(LDFLAGS) $(BUILD_)/$(LIBNAME) $(OBJ) 
	@echo Created $(LIBNAME) static library
	@echo
staticlib: $(LIBNAME)

exampledirs: dirs obj staticlib
	$(shell test -d $(EXMPL_TEMPLT)/$(SRC_NAME) || mkdir -p $(EXMPL_TEMPLT)/$(SRC_NAME))
	$(foreach mod,$(MODULES),$(foreach type,$(EXMPL_TYPES),$(shell test -d $(EXMPL_SOURCE)/$(mod)/$(type) || mkdir -p $(EXMPL_SOURCE)/$(mod)/$(type))))
	$(foreach file,$(SRC),$(shell test -h $(EXMPL_TEMPLT)/$(SRC_NAME)/$(notdir $(file)) || ln -sf  $(EXMPL_DEPTH)$(file)  $(EXMPL_TEMPLT)/$(SRC_NAME)))

examples: exampledirs
	 $(foreach mod,$(MODULES),$(foreach type,$(EXMPL_TYPES),$(shell                                                                              \
		mkdir -p $(EXMPL_DIR)/$(mod)/$(type) 					&&                                                           \
		test -d $(EXMPL_TEMPLT)/ 						&&                                                           \
		test -d $(EXMPL_DIR)/$(mod)/$(type)/ 					&&     							     \
		cp -r $(EXMPL_TEMPLT)/* $(EXMPL_DIR)/$(mod)/$(type) 			&&							     \
		test -e $(EXMPL_SOURCE)/$(mod)/$(type)/main.c 				&&                         			             \
		ln -sf ../../../$(BUILD_)/$(LIBNAME) $(EXMPL_DIR)/$(mod)/$(type)/	&&							     \
		ln -sf $(addprefix ../../$(EXMPL_SRC)/$(mod)/$(type)/,$(shell ls -x $(EXMPL_SOURCE)/$(mod)/$(type)/)) $(EXMPL_DIR)/$(mod)/$(type)/   \
	 )))
	$(shell ln -sf $(EXMPL_DEPTH)$(SOURCE_)/$(SRC_NAME).h  $(EXMPL_TEMPLT)/$(SRC_NAME)/)
	@echo
	@echo
	@echo Example folders created. Feel free to mess with the code and run make in the directory to build your code

install: all

success: $(BUILD_DIR) $(OBJ) $(LIBNAME)
	@echo
	@echo
	@echo
	@echo Cavrn Build Success!
	@echo Modules Built: $(MODULES)
	@echo Built for the $(DEVICE) Microcontroller

version :
	@$(CC) --version

clean:
	@echo
	$(shell rm -rf $(BUILD_)/ $(addprefix $(EXMPL_DIR)/,$(shell ls -x $(EXMPL_DIR))))


upload:
	@echo
	$(AVRDUDE) 

console:
	@echo
	$(AVRDUDE) 
	screen $(PORT) $(BAUD)






