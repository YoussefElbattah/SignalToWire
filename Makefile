BOARD ?= stm32l152re
BSP := bsp
SRC := src 
BUILD := build
TARGET := $(BUILD)/app.elf

BSP_INC := $(BSP)/boards/$(BOARD)/include

BIN := $(BUILD)/app.bin
HEX := $(BUILD)/app.hex

CC := arm-none-eabi-gcc
LD := arm-none-eabi-gcc

MKDIR_P := mkdir -p
RM_RF   := rm -rf

COMMON_SRCS := \
  $(wildcard src/*.c) \
  $(wildcard drivers/*.c)

ifeq ($(BOARD),stm32l152re)
  CPU := cortex-m3
  LINKER := bsp/boards/stm32l152re/link_startup/STM32L152RETX_FLASH.ld
  DEFS := -DBOARD_STM32L152RE
  BSP_SRCS := \
    bsp/boards/stm32l152re/link_startup/startup_mini.s \
    bsp/boards/stm32l152re/src/bsp_clock.c \
    bsp/boards/stm32l152re/src/bsp_gpio.c \
    bsp/boards/stm32l152re/src/bsp_timer.c \
    bsp/boards/stm32l152re/src/bsp_uart.c \
    bsp/boards/stm32l152re/src/bsp_i2c.c

else ifeq ($(BOARD),stm32u385rg)
  CPU := cortex-m33
  LINKER := bsp/boards/stm32u385rg/link_startup/STM32U385RGTXQ_FLASH.ld
  DEFS := -DBOARD_STM32U385RG
  BSP_SRCS := \
	  bsp/boards/stm32u385rg/link_startup/startup.s \
    bsp/boards/stm32u385rg/src/bsp_clock.c \
    bsp/boards/stm32u385rg/src/bsp_gpio.c \
    bsp/boards/stm32u385rg/src/bsp_timer.c \
    bsp/boards/stm32u385rg/src/bsp_uart.c \
    bsp/boards/stm32u385rg/src/bsp_i2c.c	

else
  $(error Unknown BOARD '$(BOARD)'. Use BOARD=stm32l152re or BOARD=stm32u385rg)
endif

SRCS := $(COMMON_SRCS) $(BSP_SRCS)
OBJS := $(SRCS:%=$(BUILD)/%.o)

CFLAGS 	:= -Wall -O0 -g -ffreestanding
CFLAGS 	+= -I$(BSP_INC) -Ibsp
CFLAGS  += -mcpu=$(CPU) -mthumb $(DEFS)
LDFLAGS := -T$(LINKER) -Wl,--gc-sections

all : $(TARGET)

$(BUILD)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@


$(BIN): $(TARGET)
	arm-none-eabi-objcopy -O binary $< $@


$(HEX): $(TARGET)
	arm-none-eabi-objcopy -O ihex $< $@


bin: $(BIN)
hex: $(HEX)

clean:
	$(RM_RF) $(BUILD)

.PHONY: all clean bin hex