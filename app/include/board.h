//CS704 AWSAM5 Expansion board definitions

#ifndef BOARD_H
#define BOARD_H

#define LED0_PIN            GPIO_Pin_11
#define LED0_PORT           GPIOB

#if 0
// DISCO board
#define LED1_PIN            GPIO_Pin_8
#define LED1_PORT           GPIOC
#else
// CS704 board
#define LED1_PIN            GPIO_Pin_10
#define LED1_PORT           GPIOB
#endif

#define BAT_V_ADC_PIN       GPIO_Pin_2
#define BAT_V_ADC_PORT      GPIOA

#define US0_TX_PIN            GPIO_Pin_9
#define US0_TX_PORT           GPIOA
#define US0_RX_PIN            GPIO_Pin_10
#define US0_RX_PORT           GPIOA

// Radio interface

#define RADIO_RESET_PIN     GPIO_Pin_5
#define RADIO_RESET_PORT    GPIOC
#define RADIO_SLP_TR_PIN    GPIO_Pin_1
#define RADIO_SLP_TR_PORT   GPIOB
#define RADIO_IRQ_PIN       GPIO_Pin_3
#define RADIO_IRQ_PORT      GPIOA

#define RADIO_CS_PIN        GPIO_Pin_4
#define RADIO_CS_PORT       GPIOA

#define RADIO_CLK_PIN       GPIO_Pin_5
#define RADIO_CLK_PORT      GPIOA
#define RADIO_CLK_PINSRC    GPIO_PinSource5
#define RADIO_MISO_PIN      GPIO_Pin_6
#define RADIO_MISO_PORT     GPIOA
#define RADIO_MISO_PINSRC   GPIO_PinSource6
#define RADIO_MOSI_PIN      GPIO_Pin_7
#define RADIO_MOSI_PORT     GPIOA
#define RADIO_MOSI_PINSRC   GPIO_PinSource7

#define RADIO_SPI_CLK       RCC_APB2Periph_SPI1
#define RADIO_SPI           SPI1

#define RADIO_SPI_DEFAULT   { \
                                .spi        = RADIO_SPI, \
                                .cs_port    = RADIO_CS_PORT, \
                                .cs_pin     = RADIO_CS_PIN, \
                                .mosi_port  = RADIO_MOSI_PORT, \
                                .mosi_pin   = RADIO_MOSI_PIN, \
                                .miso_port  = RADIO_MISO_PORT, \
                                .miso_pin   = RADIO_MISO_PIN, \
                                .sck_port   = RADIO_CLK_PORT, \
                                .sck_pin    = RADIO_CLK_PIN, \
                            }

// MPU interface

#define IMU_CS_PIN          GPIO_Pin_15
#define IMU_CS_PORT         GPIOA
#define IMU_CLK_PIN         GPIO_Pin_3
#define IMU_CLK_PORT        GPIOB
#define IMU_CLK_PINSRC      GPIO_PinSource3
#define IMU_MISO_PIN        GPIO_Pin_4
#define IMU_MISO_PORT       GPIOB
#define IMU_MISO_PINSRC     GPIO_PinSource4
#define IMU_MOSI_PIN        GPIO_Pin_5
#define IMU_MOSI_PORT       GPIOB
#define IMU_MOSI_PINSRC     GPIO_PinSource5

#define IMU_SYNC_PIN        GPIO_Pin_6
#define IMU_SYNC_PORT       GPIOC
#define IMU_INT_PIN         GPIO_Pin_8
#define IMU_INT_PORT        GPIOC

#define IMU_SPI_CLK         RCC_APB1Periph_SPI3
#define IMU_SPI             SPI3

#define IMU_SPI_DEFAULT     { \
                                .spi        = IMU_SPI, \
                                .cs_port    = IMU_CS_PORT, \
                                .cs_pin     = IMU_CS_PIN, \
                                .mosi_port  = IMU_MOSI_PORT, \
                                .mosi_pin   = IMU_MOSI_PIN, \
                                .miso_port  = IMU_MISO_PORT, \
                                .miso_pin   = IMU_MISO_PIN, \
                                .sck_port   = IMU_CLK_PORT, \
                                .sck_pin    = IMU_CLK_PIN, \
                            }

// uSD interface

#define SD_CS_PIN           GPIO_Pin_12
#define SD_CS_PORT          GPIOB
#define SD_CLK_PIN          GPIO_Pin_13
#define SD_CLK_PORT         GPIOB
#define SD_MOSI_PIN         GPIO_Pin_15
#define SD_MOSI_PORT        GPIOB
#define SD_MISO_PIN         GPIO_Pin_14
#define SD_MISO_PORT        GPIOB

#define SD_SPI_CLK          RCC_APB1Periph_SPI2
#define SD_SPI              SPI2

#define SD_SPI_DEFAULT      { \
                                .spi        = SD_SPI, \
                                .cs_port    = SD_CS_PORT, \
                                .cs_pin     = SD_CS_PIN, \
                                .mosi_port  = SD_MOSI_PORT, \
                                .mosi_pin   = SD_MOSI_PIN, \
                                .miso_port  = SD_MISO_PORT, \
                                .miso_pin   = SD_MISO_PIN, \
                                .sck_port   = SD_CLK_PORT, \
                                .sck_pin    = SD_CLK_PIN, \
                            }

// BME280 interface
#define BME_SDA_PIN         GPIO_Pin_7
#define BME_SDA_PORT        GPIOB
#define BME_SCL_PIN         GPIO_Pin_6
#define BME_SCL_PORT        GPIOB

#endif // BOARD_H
