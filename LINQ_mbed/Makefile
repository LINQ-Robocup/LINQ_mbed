GCC_BIN = /usr/local/bin/
OBJDIR = Builds
SOURCES = $(shell find -E . -regex '^.*\.(c(pp)?|[sS])$$' | sed -E -e 's/\.(c(pp)?|[sS])$$/.o/g')
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(SOURCES))
SYS_OBJECTS = $(shell find -E . -regex '^.*\.o$$' | sed -e 's/^.\/Builds\/.*$$//g')
INCLUDE_PATHS = -I. $(shell find -E . -regex '^.*\.h(pp)?$$' | sed -e 's/^\(.*\)\/[^\/]*$$/-I\1/g' | sort | uniq)
LIBRARY_PATHS = $(shell find -E . -regex '^.*\.a$$' | sed -e 's/^\(.*\)\/[^\/]*$$/-L\1/g' | sort | uniq)
LIBRARIES =
LINKER_SCRIPT = $(shell find -E . -regex '^.*\.ld$$')
#INTERFACE = cmsis-dap.cfg
INTERFACE = stlink-v2-1.cfg

DEBUG = 0
USE_LIBMBED = 1
USE_RTOS = 0

############################################################################### 
AS      = $(GCC_BIN)arm-none-eabi-gcc
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE    = $(GCC_BIN)arm-none-eabi-size

ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif

CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI)

AS_FLAGS = $(CPU) -c -x assembler-with-cpp

CC_FLAGS = $(CPU) -c -Wall -Wextra -fmessage-length=0 -fno-exceptions -fno-builtin -ffunction-sections -fdata-sections -funsigned-char -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer -MMD -MP

CC_SYMBOLS = -D__MBED__=1 -DDEVICE_I2CSLAVE=1 -DTARGET_LIKE_MBED -DDEVICE_PORTINOUT=1 -DTARGET_RTOS_M4_M7 -DDEVICE_LOWPOWERTIMER=1 -DDEVICE_RTC=1 -DTOOLCHAIN_object -D__CMSIS_RTOS -DTOOLCHAIN_GCC -DDEVICE_CAN=1 -DTARGET_CORTEX_M -DTARGET_DEBUG -DTARGET_LIKE_CORTEX_M4 -DDEVICE_ANALOGOUT=1 -DTARGET_M4 -DTARGET_UVISOR_UNSUPPORTED -DTARGET_STM32L4 -DDEVICE_SERIAL=1 -DMBED_BUILD_TIMESTAMP=1476584444.57 -DDEVICE_INTERRUPTIN=1 -DDEVICE_I2C=1 -DDEVICE_PORTOUT=1 -D__CORTEX_M4 -DDEVICE_STDIO_MESSAGES=1 -D__FPU_PRESENT=1 -DTARGET_FF_ARDUINO -DDEVICE_PORTIN=1 -DTARGET_STM -DTARGET_STM32L432KC -DDEVICE_SERIAL_FC=1 -D__MBED_CMSIS_RTOS_CM -DDEVICE_SLEEP=1 -DTOOLCHAIN_GCC_ARM -DDEVICE_SPI=1 -DDEVICE_SPISLAVE=1 -DDEVICE_ANALOGIN=1 -DDEVICE_PWMOUT=1 -DTARGET_NUCLEO_L432KC -DARM_MATH_CM4

CXX_FLAGS = -std=gnu++14 -fno-rtti -Wvla
#CXX_FLAGS += -Weffc++ -Wno-non-virtual-dtor -Wcast-align -Wundef -Wmissing-include-dirs -Wunused-macros -Wmissing-noreturn -Wmissing-format-attribute -Wcast-qual -Wunused -Wdisabled-optimization -Wfloat-equal -Wold-style-cast -Winline -Winit-self -Wformat-nonliteral -Wunsafe-loop-optimizations -Wunreachable-code -Wformat-security -Wlogical-op -Wformat -Woverloaded-virtual

LD_FLAGS = $(CPU) -Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_calloc_r
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

ifeq ($(USE_LIBMBED), 1)
	LIBMBED = "$(HOME)/Library/Developer/Xcode/Templates/embedded/mbed/TARGET/TARGET_STM/TARGET_STM32L4"
	SYS_OBJECTS += $(shell find -E $(LIBMBED)/TARGET_NUCLEO_L432KC -regex '^.*\.o$$')
	INCLUDE_PATHS += -I"$(HOME)/Library/Developer/Xcode/Templates/embedded/mbed" -I"$(HOME)/Library/Developer/Xcode/Templates/embedded/mbed/TARGET" -I$(LIBMBED) -I$(LIBMBED)/TARGET_NUCLEO_L432KC
	LIBRARY_PATHS += -L$(LIBMBED)/TARGET_NUCLEO_L432KC/TOOLCHAIN_GCC_ARM
	LINKER_SCRIPT = $(LIBMBED)/TARGET_NUCLEO_L432KC/TOOLCHAIN_GCC_ARM/STM32L432XX.ld
	LIBRARIES += -lmbed
	CC_SYMBOLS += -DSTM32L432xx
endif

ifeq ($(USE_RTOS), 1)
	RTOS = "$(HOME)/Library/Developer/Xcode/Templates/embedded/mbed-rtos"
	LIBRARY_PATHS += -L$(RTOS)/rtx/TARGET_CORTEX_M/TARGET_RTOS_M4/TOOLCHAIN_GCC
	INCLUDE_PATHS += -I$(RTOS) -I$(RTOS)/rtos -I$(RTOS)/rtx/TARGET_CORTEX_M
	LIBRARIES += -lrtos
	CC_SYMBOLS += -DMBED_CONF_RTOS_PRESENT=1
endif

ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0 -g
else
  CC_FLAGS += -DNDEBUG -Os
endif

all: clean build upload

createObjDir:
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

build: createObjDir $(OBJDIR)/$(PROJECT).elf

upload:
	@echo "Upload"
	$(HOME)/Library/Developer/Xcode/Templates/embedded/usr/bin/openocd -s $(HOME)/Library/Developer/Xcode/Templates/embedded/usr/share/openocd/scripts -f interface/$(INTERFACE) -f target/stm32l4x_flash.cfg -c "mt_flash $(OBJDIR)/$(PROJECT).elf"

buildAndUpload: build upload

clean:
	@if [ -d $(OBJDIR) ]; then rm -rf $(OBJDIR); fi

debug: build
	$(HOME)/Library/Developer/Xcode/Templates/embedded/usr/bin/openocd -s $(HOME)/Library/Developer/Xcode/Templates/embedded/usr/share/openocd/scripts -f interface/$(INTERFACE) -f target/stm32l4x_flash.cfg &
	$(HOME)/Library/Developer/Xcode/Templates/embedded/usr/bin/arm-none-eabi-insight $(CURDIR)/$(OBJDIR)/$(PROJECT).elf
	@killall openocd

$(OBJDIR)/%.o:	%.asm
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(OBJDIR)/%.o: 	%.s
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(OBJDIR)/%.o: 	%.S
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(OBJDIR)/%.o: 	%.c
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99 $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.o: 	%.cpp
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	@echo Link
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ -Wl,--start-group $(LIBRARIES) -Wl,--end-group $(LD_SYS_LIBS)
	$(SIZE) $@

$(OBJDIR)/$(PROJECT).bin: $(OBJDIR)/$(PROJECT).elf
	@echo Copy
	$(OBJCOPY) -O binary $< $@

-include $(OBJECTS:.o=.d)
