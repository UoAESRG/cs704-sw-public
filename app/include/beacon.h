
#ifndef BEACON_H
#define BEACON_H

#include <stdint.h>

#include "at86rf212/at86rf212.h"

void send_beacon(struct at86rf212_s *radio, uint16_t pan, uint16_t from, uint16_t to, uint8_t seq);
void run_master(struct at86rf212_s *radio, uint16_t pan, uint16_t address);
void run_slave(struct at86rf212_s *radio, uint16_t pan, uint16_t address);

#endif
