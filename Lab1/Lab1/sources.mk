SRC_DIR    = Sources
INC_DIR    = Includes
LINKER_DIR = Linker

SRCS = \
$(SRC_DIR)/main.c             \
$(LINKER_DIR)/stm32_startup.c \
$(SRC_DIR)/GPIO_driver.c      \
$(SRC_DIR)/button.c           \
$(SRC_DIR)/system_stm32f4xx.c

INCLUDES = \
-I$(INC_DIR)       \
-ICMSIS/STM32F4xx  \
-ICMSIS
