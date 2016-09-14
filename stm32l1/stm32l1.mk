# Makefile for STM32L1 components

# Include directories
STM32_INC = -I${STM32_BASE}/include -I${STM32_BASE}/include/CMSIS \
-I${STM32_BASE}/include/drivers -I${STM32_BASE}/include/usb

# Locate sources and generate object names
STM32_LIB = ${BUILD_DIR}/libstm32l1.a
STM32_CORE_SRC = $(wildcard $(STM32_BASE)/source/*.c)
STM32_CORE_ASM =  $(wildcard $(STM32_BASE)/source/*.S)
STM32_CORE_OBJ = $(patsubst $(STM32_BASE)/source/%.c, ${BUILD_DIR}/%.o, $(STM32_CORE_SRC)) \
                 $(patsubst $(STM32_BASE)/source/%.S, ${BUILD_DIR}/%.o, $(STM32_CORE_ASM))
STM32_DRIVER_SRC = $(wildcard $(STM32_BASE)/source/drivers/*.c)
STM32_DRIVER_OBJ = $(patsubst $(STM32_BASE)/source/drivers/%.c, ${BUILD_DIR}/%.o, $(STM32_DRIVER_SRC))

STM32_USB_SRC = $(wildcard $(STM32_BASE)/source/usb/*.c)
STM32_USB_OBJ = $(patsubst $(STM32_BASE)/source/usb/%.c, ${BUILD_DIR}/%.o, $(STM32_USB_SRC))

STM32_SRC = ${STM32_CORE_SRC} ${STM32_DRIVER_SRC} ${STM32_USB_SRC}
STM32_OBJ = ${STM32_CORE_OBJ} ${STM32_DRIVER_OBJ} ${STM32_USB_OBJ}
STM32_DEPS := $(patsubst %.o, %.d, ${STM32_OBJ})
-include ${STM32_DEPS}

# Specify linker file
STM32_LD = ${STM32_BASE}/STM32L152ZC_FLASH.ld

# Source to Object Mappings
${BUILD_DIR}/%.o: ${STM32_BASE}/source/%.c
	@echo "[libstm32l1] building: $<"
	@${CC} ${CFLAGS} -c $< -o $@

${BUILD_DIR}/%.o: ${STM32_BASE}/source/%.S
	@echo "[libstm32l1] building: $<"
	@${CC} ${CFLAGS} -c $< -o $@

${BUILD_DIR}/%.o: ${STM32_BASE}/source/drivers/%.c
	@echo "[libstm32l1] building: $<"
	@${CC} ${CFLAGS} -c $< -o $@

${BUILD_DIR}/%.o: ${STM32_BASE}/source/usb/%.c
	@echo "[libstm32l1] building: $<"
	@${CC} ${CFLAGS} -c $< -o $@

${STM32_LIB}: ${STM32_OBJ}
	@echo "[libstm32l1] linking STM32 device library"
	@${AR} qc $@ $^
