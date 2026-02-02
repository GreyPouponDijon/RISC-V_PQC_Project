OUTPUT_FILENAME = merged_cm33_vpr
TARGET ?= nrf54lm20
FOLDER ?= .
BUILD ?= $(FOLDER)/build-$(TARGET)

include makefile.cm33
include makefile.vpr

.PHONY: all hex deploy
all: hex

## Create binary .hex file from the .out file
hex: $(BUILD)/$(OUTPUT_FILENAME).hex

$(BUILD)/$(OUTPUT_FILENAME).hex: $(VPR_BUILD)/$(VPR_OUTPUT_FILENAME).hex $(CM33_BUILD)/$(CM33_OUTPUT_FILENAME).hex
	$(MKDIR) -p $(BUILD)
	$(ECHO) "Merging binaries into $(BUILD)/$(OUTPUT_FILENAME).hex"
	$(Q)python3 -c 'import intelhex; cm33 = intelhex.IntelHex("$(CM33_BUILD)/$(CM33_OUTPUT_FILENAME).hex"); vpr = intelhex.IntelHex("$(VPR_BUILD)/$(VPR_OUTPUT_FILENAME)_nvm.hex"); cm33.merge(vpr, overlap="replace"); cm33.tofile("$(BUILD)/$(OUTPUT_FILENAME).hex", format="hex")'

deploy: $(BUILD)/$(OUTPUT_FILENAME).hex
	nrfutil device program --firmware $<
	nrfutil device reset

include mk/mkrules.mk

