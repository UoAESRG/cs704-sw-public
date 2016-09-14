

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

#include "stm32l1xx.h"

struct spi_ctx_s {
    SPI_TypeDef* spi;
    GPIO_TypeDef* cs_port;
    uint32_t cs_pin;
    GPIO_TypeDef* mosi_port;
    uint32_t mosi_pin;
    GPIO_TypeDef* miso_port;
    uint32_t miso_pin;
    GPIO_TypeDef* sck_port;
    uint32_t sck_pin;
};

void SPI_init(struct spi_ctx_s *spi_ctx, uint8_t cpol, uint8_t edge);
int SPI_transfer(struct spi_ctx_s *spi_ctx, int len, uint8_t* data_out, uint8_t* data_in);

#endif // GPIO_H
