
#include "spi.h"

#include <stdlib.h>
#include <stdint.h>

#include "stm32l1xx.h"

#include "board.h"

void SPI_init(struct spi_ctx_s *spi_ctx, uint8_t cpol, uint8_t edge)
{
    GPIO_InitTypeDef gpio_init;
    SPI_InitTypeDef  spi_init;

    gpio_init.GPIO_Mode = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_DOWN;
    gpio_init.GPIO_Speed = GPIO_Speed_40MHz;

    // SPI CLK
    gpio_init.GPIO_Pin = spi_ctx->sck_pin;
    GPIO_Init(spi_ctx->sck_port, &gpio_init);

    // SPI MOSI
    gpio_init.GPIO_Pin = spi_ctx->mosi_pin;
    GPIO_Init(spi_ctx->mosi_port, &gpio_init);

    // SPI MISO
    gpio_init.GPIO_Pin = spi_ctx->miso_pin;
    GPIO_Init(spi_ctx->miso_port, &gpio_init);

    // SPI CS
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Pin = spi_ctx->cs_pin;
    GPIO_Init(spi_ctx->cs_port, &gpio_init);

    // Configure SPI
    SPI_I2S_DeInit(spi_ctx->spi);
    spi_init.SPI_Mode = SPI_Mode_Master;
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_DataSize = SPI_DataSize_8b;


#if 0
    spi_init.SPI_CPOL = SPI_CPOL_Low;
    spi_init.SPI_CPHA = SPI_CPHA_1Edge;
#else
    if (cpol == 0) {
        spi_init.SPI_CPOL = SPI_CPOL_Low;
    } else {
        spi_init.SPI_CPOL = SPI_CPOL_High;
    }

    if (edge == 0) {
        spi_init.SPI_CPHA = SPI_CPHA_1Edge;
    } else {
        spi_init.SPI_CPHA = SPI_CPHA_2Edge;
    }
#endif

    spi_init.SPI_NSS = SPI_NSS_Soft;
    spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
    spi_init.SPI_CRCPolynomial = 7;
    SPI_Init(spi_ctx->spi, &spi_init);

    // Ensure CS is de-asserted
    spi_ctx->cs_port->BSRRL = spi_ctx->cs_pin;

    // Enable SPI
    SPI_Cmd(spi_ctx->spi, ENABLE);

    // Set CS mode to software defined
    SPI_NSSInternalSoftwareConfig(spi_ctx->spi, SPI_NSSInternalSoft_Set);


}

int SPI_transfer(struct spi_ctx_s *spi_ctx, int len, uint8_t* data_out, uint8_t* data_in)
{
    uint32_t flags;

    // Assert CS
    spi_ctx->cs_port->BSRRH = spi_ctx->cs_pin;

    // Transfer data
    for (int i = 0; i < len; i++) {
        // Write byte
        SPI_I2S_SendData(spi_ctx->spi, data_out[i]);
        // Await completion
        while ((flags = SPI_I2S_GetFlagStatus(spi_ctx->spi, SPI_I2S_FLAG_RXNE)) == 0);

        // Read byte
        data_in[i] = SPI_I2S_ReceiveData(spi_ctx->spi);

        // Await ready for next byte
        while ((flags = SPI_I2S_GetFlagStatus(spi_ctx->spi, SPI_I2S_FLAG_BSY)) != 0);
    }

    // Deassert CS
    spi_ctx->cs_port->BSRRL = spi_ctx->cs_pin;

    return 0;
}
