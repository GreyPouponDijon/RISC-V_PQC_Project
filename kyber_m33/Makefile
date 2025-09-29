PROJECT ?= kyber_m33
OUTDIR ?= build

REF_DIR = ./ref
DRIVERS_DIR = ./drivers
MDK_DIR = ./mdk_8.72.2
CMSIS_DIR = .cmsis5_core_include
KYBER_SRCS += $(REF_DIR)/kem.c $(REF_DIR)/indcpa.c $(REF_DIR)/polyvec.c $(REF_DIR)/poly.c $(REF_DIR)/ntt.c $(REF_DIR)/cbd.c \
					 $(REF_DIR)/reduce.c $(REF_DIR)/verify.c $(REF_DIR)/fips202.c $(REF_DIR)/symmetric_shake.c 
PLAT_SRCS  += $(MDK_DIR)/system_nrf54l.c
PLAT_SRCS  += $(DRIVERS_DIR)/print_lib.c
PLAT_SRCS  += $(DRIVERS_DIR)/uarte.c
STARTUP = $(MDK_DIR)/gcc_startup_nrf54l15_application.S

LINKER_SCRIPTS ?= -T target.ld

KYBER512_SRC := $(REF_DIR)/test/test_kyber.c
SPEED512_SRC := $(REF_DIR)/test/test_speed.c

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

OBJS  := $(patsubst %.c,  $(OUTDIR)/%.o, $(KYBER_SRCS) $(PLATSRC)) \
				 $(patsubst %.S,  $(OUTDIR)/%.o, $(STARTUP))

KYBER512_OBJS := $(OBJS) $(OUTDIR)/$(TEST_KYBER512_SRC:.c=.o)
SPEED512_OBJS := $(OBJS) $(OUTDIR)/$(TEST_SPEED512_SRC:.c=.o)


# -------- Phony --------
.PHONY: all clean size

all: $(OUTDIR)/test_kyber512.elf $(OUTDIR)/test_kyber512.bin $(OUTDIR)/test_kyber512.hex \
     $(OUTDIR)/test_speed512.elf $(OUTDIR)/test_speed512.bin $(OUTDIR)/test_speed512.hex

# -------- Compile rules --------
$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(GCC_GCC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/%.o: %.S
	@mkdir -p $(@D)
	$(GCC_GCC) $(ARCH_OPT) -c $< -o $@

# -------- Link rules --------
$(OUTDIR)/test_kyber512.elf: $(KYBER512_OBJS)
	@mkdir -p $(@D)
	$(GCC_GCC) $(ARCH_OPT) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	$(SIZE) $@

$(OUTDIR)/test_speed512.elf: $(SPEED512_OBJS)
	@mkdir -p $(@D)
	$(GCC_GCC) $(ARCH_OPT) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	$(SIZE) $@

# -------- Format conversion --------
$(OUTDIR)/%.bin: $(OUTDIR)/%.elf
	$(OBJCOPY) -O binary $< $@

$(OUTDIR)/%.hex: $(OUTDIR)/%.elf
	$(OBJCOPY) -O ihex $< $@

# -------- Housekeeping --------
clean:
	rm -rf $(OUTDIR)

# Auto-include deps
DEPS := $(KYBER512_OBJS:.o=.d) $(SPEED512_OBJS:.o=.d)
-include $(DEPS)
