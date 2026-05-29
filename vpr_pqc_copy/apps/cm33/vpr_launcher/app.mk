#Override the default memory ld file from linkerscripts/ folder.
CM33_LD_FILES += $(CM33_APP_DIR)/memory_nvm.ld

CM33_APP_CUSTOM_SYSTEM_FILE := 0

CM33_SRC_S = $(CM33_APP_DIR)/startup.S
