
#include "gpio.h"

#include "board.h"
#include "stm32l1xx.h"

void GPIO_init()
{
    // Enable GPIO clocks
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    // Setup LED pins
    GPIO_set_output(LED0_PORT, LED0_PIN);
    GPIO_set_output(LED1_PORT, LED1_PIN);

    // Setup IMU pins
    GPIO_set_output(IMU_SYNC_PORT, IMU_SYNC_PIN);
    GPIO_set_input(IMU_INT_PORT, IMU_INT_PIN);

    // Enable IMU SPI clock and set routes
    RCC_APB1PeriphClockCmd(IMU_SPI_CLK, ENABLE);
    GPIO_PinAFConfig(IMU_CLK_PORT,  IMU_CLK_PINSRC,  GPIO_AF_SPI3);
    GPIO_PinAFConfig(IMU_MOSI_PORT, IMU_MOSI_PINSRC, GPIO_AF_SPI3);
    GPIO_PinAFConfig(IMU_MISO_PORT, IMU_MISO_PINSRC, GPIO_AF_SPI3);

    // Setup radio pins
    GPIO_set_output(RADIO_RESET_PORT, RADIO_RESET_PIN);
    GPIO_set_output(RADIO_SLP_TR_PORT, RADIO_SLP_TR_PIN);

    // Enable radio SPI clock and set routes
    RCC_APB2PeriphClockCmd(RADIO_SPI_CLK, ENABLE);
    GPIO_PinAFConfig(RADIO_CLK_PORT,  RADIO_CLK_PINSRC,  GPIO_AF_SPI1);
    GPIO_PinAFConfig(RADIO_MOSI_PORT, RADIO_MOSI_PINSRC, GPIO_AF_SPI1);
    GPIO_PinAFConfig(RADIO_MISO_PORT, RADIO_MISO_PINSRC, GPIO_AF_SPI1);
    
}

void GPIO_set_output(GPIO_TypeDef *port, uint32_t pin)
{
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_Speed = GPIO_Speed_40MHz;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Pin = pin;
    GPIO_Init(port, &gpio_init);
}

void GPIO_set_input(GPIO_TypeDef *port, uint32_t pin)
{
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_Speed = GPIO_Speed_40MHz;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Pin = pin;
    GPIO_Init(port, &gpio_init);
}

void GPIO_write(GPIO_TypeDef *port, uint32_t pin, uint8_t val)
{
    if (val != 0) {
        port->BSRRL = pin;
    } else {
        port->BSRRH = pin;
    }
}

int GPIO_read(GPIO_TypeDef *port, uint32_t pin)
{
    return ((port->IDR & pin) == 0) ? 0 : 1;
}
