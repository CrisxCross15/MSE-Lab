include sources.mk
EXEC    = app.elf
OBJ_DIR = Objects

OPENOCD = "C:/ST/STM32CubeIDE_2.0.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.openocd.win32_2.4.300.202509300731/tools/bin/openocd.exe"

OPENOCD_SCRIPTS = "C:/ST/STM32CubeIDE_2.0.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.debug.openocd_2.3.200.202510310951/resources/openocd/st_scripts"

LINKER_FILE = Linker/STM32f4.ld
CPU         = cortex-m4
ARCH        = armv7e-m
SPECS       = nosys.specs
FPU         = fpv4-sp-d16

ARCHFLAGS = \
-mcpu=$(CPU) \
-mthumb \
-march=$(ARCH) \
-mfloat-abi=hard \
-mfpu=$(FPU) \
--specs=$(SPECS)

DEVICE_DEF = -DSTM32F411xE

CFLAGS = \
-g \
-O0 \
-std=c99 \
-Wall \
-Werror \
$(ARCHFLAGS) \
$(DEVICE_DEF)

LDFLAGS = -nostdlib -T $(LINKER_FILE)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(sort $(dir $(SRCS)))

CC = arm-none-eabi-gcc

# ── Regla de compilación: .c → Objects/*.o ───────────────────────────────────
$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

# ── Build ─────────────────────────────────────────────────────────────────────
.PHONY: build
build : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@

# ── Flash ─────────────────────────────────────────────────────────────────────
.PHONY: flash
flash :
	$(OPENOCD) -s $(OPENOCD_SCRIPTS) \
	-f interface/stlink-dap.cfg \
	-f target/stm32f4x.cfg \
	-c "program $(EXEC) verify reset" \
	-c shutdown

# ── Clean ─────────────────────────────────────────────────────────────────────
.PHONY: clean
clean :
	rm -rf $(OBJ_DIR) $(EXEC)
