# Makefile for AT86RF212B library

# Include directories
AT86RF212_INC = -I${AT86RF212_BASE}/lib

# Locate sources and generate object names
AT86RF212_LIB = ${BUILD_DIR}/libat86rf212.a
AT86RF212_SRC = $(wildcard $(AT86RF212_BASE)/lib/source/*.c)
AT86RF212_OBJ = $(patsubst $(AT86RF212_BASE)/lib/source/%.c, ${BUILD_DIR}/%.o, $(AT86RF212_SRC))
AT86RF212_DEPS := $(patsubst %.o, %.d, ${AT86RF212_OBJ})
-include ${AT86RF212_DEPS}

# Source to Object Mappings
${BUILD_DIR}/%.o: ${AT86RF212_BASE}/lib/source/%.c
	@echo "[libat86rf212] building: $<"
	@${CC} ${CFLAGS} -c $< -o $@

${AT86RF212_LIB}: ${AT86RF212_OBJ}
	@echo "[libat86rf212] linking AT86RF212 driver library"
	@${AR} qc $@ $^

