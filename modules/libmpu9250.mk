# Makefile for MPU9250 library

# Include directories
MPU9250_INC = -I${MPU9250_BASE}/lib

# Locate sources and generate object names
MPU9250_LIB = ${BUILD_DIR}/libmpu9250.a
MPU9250_SRC = $(wildcard $(MPU9250_BASE)/lib/source/*.c)
MPU9250_OBJ = $(patsubst $(MPU9250_BASE)/lib/source/%.c, ${BUILD_DIR}/%.o, $(MPU9250_SRC))
MPU9250_DEPS := $(patsubst %.o, %.d, ${MPU9250_OBJ})
-include ${MPU9250_DEPS}

# Source to Object Mappings
${BUILD_DIR}/%.o: ${MPU9250_BASE}/lib/source/%.c
	@echo "[libmpu9250] building: $<"
	@${CC} ${CFLAGS} -c $< -o $@

${MPU9250_LIB}: ${MPU9250_OBJ}
	@echo "[libmpu9250] linking MPU9250 driver library"
	@${AR} rc $@ $?

