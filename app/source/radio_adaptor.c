
#include "radio_adaptor.h"

#include <stdint.h>
#include <stdlib.h>

#include "stm32l1xx.h"

#include "board.h"
#include "gpio.h"
#include "spi.h"

int radio_set_reset(void* ctx, uint8_t val)
{
    GPIO_write(RADIO_RESET_PORT, RADIO_RESET_PIN, val);
    return 0;
}

int radio_set_slp_tr(void* ctx, uint8_t val)
{
    GPIO_write(RADIO_SLP_TR_PORT, RADIO_SLP_TR_PIN, val);
    return 0;
}

int radio_get_irq(void* ctx, uint8_t *val)
{
    //*val = gpio_read(RADIO_IRQ_PORT, RADIO_IRQ_PIN);
    return 0;
}

int radio_spi_transfer(void* ctx, int len, uint8_t* data_out, uint8_t* data_in)
{
    struct spi_ctx_s *spi_ctx = (struct spi_ctx_s *) ctx;
    SPI_transfer(spi_ctx, len, data_out, data_in);
    return 0;
}

