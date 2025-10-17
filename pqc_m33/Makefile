




GCC_PATH := /usr/bin
GCC_PREFIX := $(GCC_PATH)/arm-none-eabi-
GCC_GCC := $(GCC_PREFIX)gcc
GCC_OBJDUMP := $(GCC_PREFIX)objdump
GCC_OBJCOPY := $(GCC_PREFIX)objcopy
GCC_SIZE := $(GCC_PREFIX)size


DRIVERS_DIR = ./drivers
MDK_DIR = ./mdk_8.72.2
CMSIS_DIR = ./cmsis5_core_include
C_FILES += $(MDK_DIR)/system_nrf54l.c
C_FILES += $(DRIVERS_DIR)/print_lib.c
C_FILES += $(DRIVERS_DIR)/uarte.c
C_FILES += $(DRIVERS_DIR)/nrf_config.c
S_FILES = $(MDK_DIR)/gcc_startup_nrf54l15_application.S

KYBER_DIR = ./ref
KYBER_TEST_DIR = $(KYBER_DIR)/test

SLH_DSA_DIR = ./slh

LINKER_SCRIPTS ?= -T target.ld
OUTDIR = ./build

C_DEFINES =  -D__START=main -D__MTVT_PRESENT  -D__STACK_SIZE=2048 -D__HEAP_SIZE=2048 -D__STARTUP_CLEAR_BSS
C_DEFINES += -DCONFIG_HW_UARTE_INSTANCE=0x500C6000
C_DEFINES += -DNRF54L15_XXAA
C_DEFINES += -DNRF_SKIP_SAU_CONFIGURATION
C_DEFINES += -DNRF_APPLICATION

VPATH := $(MDK_DIR):$(DRIVERS_DIR)

ARCH_OPT = -mthumb -mabi=aapcs  -mcmse -march=armv8-m.main+dsp -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard

WARNINGS = -Wall -Wextra -Wshadow -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings  -Wredundant-decls -Wstrict-prototypes  -Wpedantic

OPTIMISATION_OPTIONS = -O3 -g
LIB_OPT :=  -ffreestanding  --specs=nano.specs -lgcc -lc
LINKER_OPTIONS := -Wl,--gc-sections -lgcc -lc



CFLAGS += $(ARCH_OPT)
CFLAGS += $(OPTIMISATION_OPTIONS)
CFLAGS += $(WARNINGS)
CFLAGS += $(LIB_OPT)
CFLAGS += $(DEFINITIONS)

INCDIR += -I. -I $(MDK_DIR) -I $(DRIVERS_DIR) -I $(CMSIS_DIR)
# Kyber
ifeq ($(ALG), kyber)
	TARGET := m33_kyber
	KYBER_SOURCES = kem.c indcpa.c polyvec.c poly.c ntt.c cbd.c reduce.c verify.c fips202.c symmetric-shake.c
	REF_SOURCES := $(addprefix ref/, $(KYBER_SOURCES))
	C_FILES += $(REF_SOURCES)
	C_FILES += test_speed.c randombytes.c cpucycles.c speed_print.c
	INCDIR += -I $(KYBER_DIR) -I $(KYBER_TEST_DIR) 
  VPATH := $(MDK_DIR):$(DRIVERS_DIR):$(KYBER_DIR):$(KYBER_TEST_DIR)
else ifeq ($(ALG), slh-dsa)
	TARGET := m33_slh-dsa
	SLH_SOURCES = $(wildcard $(SLH_DSA_DIR)/*.c) 
	C_FILES += $(SLH_SOURCES)
	INCDIR += -I $(SLH_DSA_DIR)	
	VPATH := $(MDK_DIR):$(DRIVERS_DIR):$(SLH_DSA_DIR)
	CFLAGS += -DNDEBUG
else
	$(error Unknown algorithm '$(ALG)')
endif


#INCDIR += -I. -I $(MDK_DIR) -I $(DRIVERS_DIR) -I $(CMSIS_DIR) -I $(KYBER_DIR) -I $(KYBER_TEST_DIR)

OBJS  := $(patsubst %.c,  $(OUTDIR)/%.o, $(notdir $(C_FILES)))
S_OBJ := $(patsubst %.S,  $(OUTDIR)/%.o, $(notdir $(S_FILES)))

all: print dis ihex hex map bin lst size $(OUTDIR)

OBJ_DIRS = $(sort $(dir $(OBJS)))
$(OBJS): | $(OBJ_DIRS)
$(OBJ_DIRS):
	mkdir -p $@

print:
	@echo "$(C_FILES)"


$(OUTDIR)/%.o: %.c
	$(GCC_GCC) $(INCDIR) $(C_DEFINES) $(CFLAGS)  -o $@ -c $<

$(OUTDIR)/%.o: %.S
	$(GCC_GCC) $(INCDIR) $(C_DEFINES) $(CFLAGS)  -o $@ -c $<

$(OUTDIR)/$(TARGET).elf: $(OBJS) $(S_OBJ) $(OUTDIR)
	$(GCC_GCC) $(OBJS) $(S_OBJ) $(LIB_OPT) -L$(MDK_DIR) $(LINKER_SCRIPTS) $(LINKER_OPTIONS)  $(ARCH_OPT) -o $(OUTDIR)/$(TARGET).elf

bin: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJCOPY) -O binary $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).bin

lst: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJDUMP) -d $(OUTDIR)/$(TARGET).elf > $(OUTDIR)/$(TARGET).lst

dis: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJDUMP) -S $< > $(OUTDIR)/$(TARGET).dis

ihex: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJCOPY) -O ihex  $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).ihex

hex: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJCOPY) -O verilog  $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).hex

map: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJDUMP) -t   $(OUTDIR)/$(TARGET).elf > $(OUTDIR)/$(TARGET).map

size: $(OUTDIR)/$(TARGET).elf
	$(GCC_SIZE) $<

ml_kem: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJCOPY) -O binary $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).bin


.PHONY: clean
clean:
	rm -rf $(OUTDIR)



