
#include "imu_adaptor.h"

#include <stdint.h>
#include <stdlib.h>

#include "stm32l1xx.h"

#include "board.h"
#include "gpio.h"
#include "spi.h"

int imu_spi_transfer(void* ctx, int len, uint8_t* data_out, uint8_t* data_in)
{
    struct spi_ctx_s *spi_ctx = (struct spi_ctx_s *) ctx;
    SPI_transfer(spi_ctx, len, data_out, data_in);
    return 0;
}

