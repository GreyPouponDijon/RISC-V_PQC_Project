


PROJECT ?= kyber_m33
BUILD_DIR ?= ./build

REF_DIR = ./ref
DRIVERS_DIR = ./drivers
MDK_DIR = ./mdk_8.72.2
CMSIS_DIR = .cmsis5_core_include
C_FILES += $(REF_DIR)/kem.c $(REF_DIR)/indcpa.c $(REF_DIR)/polyvec.c $(REF_DIR)/poly.c $(REF_DIR)/ntt.c $(REF_DIR)/cbd.c \
					 $(REF_DIR)/reduce.c $(REF_DIR)/verify.c $(REF_DIR)/fips202.c $(REF_DIR)/symmetric_shake.c 
C_FILES += $(MDK_DIR)/system_nrf54l.c
C_FILES += $(DRIVERS_DIR)/print_lib.c
C_FILES += $(DRIVERS_DIR)/uarte.c
H_FILES += $(REF_DIR)/params.h $(REF_DIR)/kem.h $(REF_DIR)/indcpa.h $(REF_DIR)/polyvec.h $(REF_DIR)/poly.h $(REF_DIR)/ntt.h \ 
					 $(REF_DIR)/cbd.h $(REF_DIR) $(REF_DIR)/cbd.h $(REF_DIR)/reduce.c $(REF_DIR)/verify.h $(REF_DIR)/symmetric.h \
				   $(REF_DIR)/fips202.h

S_FILES = $(MDK_DIR)/gcc_startup_nrf54l15_application.S

LINKER_SCRIPTS ?= -T target.ld
OUTDIR = ./build

GCC_PATH := /usr/bin
GCC_PREFIX := $(GCC_PATH)/arm-none-eabi-
GCC_GCC := $(GCC_PREFIX)gcc
GCC_OBJDUMP := $(GCC_PREFIX)objdump
GCC_OBJCOPY := $(GCC_PREFIX)objcopy
GCC_SIZE := $(GCC_PREFIX)size

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

INCDIR += -I. -I $(MDK_DIR) -I $(DRIVERS_DIR) -I $(CMSIS_DIR) -I $(REF_DIR)

OBJS  := $(patsubst %.c,  $(OUTDIR)/%.o, $(notdir $(C_FILES)))
S_OBJ := $(patsubst %.S,  $(OUTDIR)/%.o, $(notdir $(S_FILES)))

all: bin test_kyber512 $(OUTDIR)

OBJ_DIRS = $(sort $(dir $(OBJS)))
$(OBJS): | $(OBJ_DIRS)
$(OBJ_DIRS):
	mkdir -p $@


$(OUTDIR)/%.o: %.c
	$(GCC_GCC) $(INCDIR) $(C_DEFINES) $(CFLAGS)  -o $@ -c $<

$(OUTDIR)/%.o: %.S
	$(GCC_GCC) $(INCDIR) $(C_DEFINES) $(CFLAGS)  -o $@ -c $<

$(OUTDIR)/$(TARGET).elf: $(OBJS) $(S_OBJ) $(OUTDIR)
	$(GCC_GCC) $(OBJS) $(S_OBJ) $(LIB_OPT) -L$(MDK_DIR) $(LINKER_SCRIPTS) $(LINKER_OPTIONS)  $(ARCH_OPT) -o $(OUTDIR)/$(TARGET).elf

test_kyber512:
	$(GCC_GCC) $(C_FLAGS) -DKYBER_K=2 $(C_FILES) $(REF_DIR)/random_bytes.c $(REF_DIR)/test/test_kyber.c -O binary $@


bin: $(OUTDIR)/$(TARGET).elf
	$(GCC_OBJCOPY) -O binary $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).bin



