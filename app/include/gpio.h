

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "stm32l1xx.h"

void GPIO_init();

void GPIO_set_output(GPIO_TypeDef *port, uint32_t pin);
void GPIO_set_input(GPIO_TypeDef *port, uint32_t pin);
void GPIO_write(GPIO_TypeDef *port, uint32_t pin, uint8_t val);
int GPIO_read(GPIO_TypeDef *port, uint32_t pin);

#endif // GPIO_H
