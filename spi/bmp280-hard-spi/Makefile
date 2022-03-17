TARGET = hard-spi

# Build path
BUILD_DIR = build

# Source files
C_SOURCES  = \
src/main.c \
src/rcc.c \
src/gpio.c \
src/spi.c \
src/usart.c \
src/timer.c \
src/bmp280.c \
drivers/src/system_stm32f4xx.c

ASM_SOURCES = drivers/src/startup_stm32f411xe.s

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# mcu
MCU = -mcpu=cortex-m4 -mthumb \
-mfpu=fpv4-sp-d16 -mfloat-abi=hard

# C defines
C_DEFS =  \
-DSTM32F411xE

# C includes
C_INCLUDES = \
-Iinc \
-Idrivers/inc

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -Og -g -Wall -fdata-sections -ffunction-sections


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = drivers/ld/STM32F411CEUx_FLASH.ld

LDFLAGS = $(MCU) -specs=nano.specs -specs=nosys.specs -T$(LDSCRIPT) \
-Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# addprefix: adds $(BUILD_DIR) to each file
# notdir: extracts only the filename (leaving subdirs)
# .c=.o: replaces all '.c' filetypes with '.o'
# dir: extracts only the directory part of each file
# sort: sorts files/dirs alphabetically & removing duplicates

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# building .c files
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $< -o $@

# building .s files
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)

flash-uart: all
	stm32flash -w $(BUILD_DIR)/$(TARGET).bin -v -g 0x0 /dev/ttyUSB0

flash-usb: all
	dfu-util -a 0 -d 0483:df11 -D $(BUILD_DIR)/$(TARGET).bin -s 0x08000000:leave -R

flash-stlink: all
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000