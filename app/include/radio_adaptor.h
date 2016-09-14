
#ifndef RADIO_ADAPTOR_H
#define RADIO_ADAPTOR_H

#include <stdint.h>

#define RADIO_ADAPTOR_DEFAULT {\
    .spi_transfer = radio_spi_transfer, \
    .set_reset = radio_set_reset, \
    .set_slp_tr = radio_set_slp_tr, \
    .get_irq = radio_get_irq, \
    .get_dig1 = NULL, \
    .get_dig2 = NULL \
}

int radio_set_reset(void* ctx, uint8_t val);
int radio_set_slp_tr(void* ctx, uint8_t val);
int radio_get_irq(void* ctx, uint8_t *val);
int radio_spi_transfer(void* ctx, int len, uint8_t* data_out, uint8_t* data_in);

#endif
