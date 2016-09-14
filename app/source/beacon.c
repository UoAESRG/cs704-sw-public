
#include "beacon.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "gpio.h"

#include "fifteenfour.h"
#include "at86rf212/at86rf212.h"


#define BEACON_TIME_MS      200         //!< Timeout between beacon frames

extern void delay_ms(uint32_t ms);
extern void error_flash(int id, int error);

void send_beacon(struct at86rf212_s *radio, uint16_t pan, uint16_t from, uint16_t to, uint8_t seq)
{
    int res;
    struct fifteen_four_header_s header_out = FIFTEEN_FOUR_DEFAULT_HEADER(pan, from, to, seq);
    uint8_t test_data[] = {0xaa, 0xbb, 0xcc, 0xdd};

    // Build packet
    uint8_t packet[sizeof(struct fifteen_four_header_s) + sizeof(test_data)];
    memcpy(packet, &header_out, sizeof(struct fifteen_four_header_s));
    memcpy(packet + sizeof(struct fifteen_four_header_s), test_data, sizeof(test_data));

    // Start send
    res = at86rf212_start_tx(radio, sizeof(packet), packet);
    if (res < 0) {
        error_flash(9, -res);
    }

    // Await completion
    while ((res = at86rf212_check_tx(radio)) == 0) {
        delay_ms(1);
    }
}

void run_master(struct at86rf212_s *radio, uint16_t pan, uint16_t address)
{
    uint8_t seq = 0;

    while (1) {
        LED0_PORT->ODR ^= LED0_PIN;

        // Send beacon packet
        send_beacon(radio, pan, address, address + 1, seq);

        // Increment sequence number
        seq ++;

        delay_ms(BEACON_TIME_MS);
    }
}

void run_slave(struct at86rf212_s *radio, uint16_t pan, uint16_t address)
{
    struct fifteen_four_header_s header_in;

    uint8_t len_in;
    uint8_t data_in[128];
    uint8_t seq = 0;
    int res;

    // Enter RX mode
    res = at86rf212_start_rx(radio);
    if (res < 0) {
        error_flash(10, res);
    }

    while (1) {
        // Check for received packets
        res = at86rf212_check_rx(radio);
        if (res < 0) {
            at86rf212_start_rx(radio);
            continue;
        }

        // If nothing is received, delay and then go around again
        if (res == 0) {
            delay_ms(1);
            continue;
        }

        // Fetch the received packet
        res = at86rf212_get_rx(radio, &len_in, data_in);
        if (res < 0) {
            at86rf212_start_rx(radio);
            continue;
        }

        // Check packet length
        if (len_in == (sizeof(struct fifteen_four_header_s) + 4 + 2 + 3)) {
            memcpy(&header_in, data_in, len_in);

            //Repeat beacon if match occurs
            if ((header_in.pan == pan) && header_in.dest == address) {
                LED1_PORT->ODR ^= LED1_PIN;

                // Wait a moment for slower devices to re-enter rx mode
                delay_ms(5);

                // Send beacon packet on
                send_beacon(radio, pan, address, address + 1, seq);

                // Increment sequence number
                seq ++;
            }
        }

        at86rf212_start_rx(radio);
    }

    error_flash(11, 1);
}

