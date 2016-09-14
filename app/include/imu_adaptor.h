
#ifndef IMU_ADAPTOR_H
#define IMU_ADAPTOR_H

#include <stdint.h>

#define IMU_ADAPTOR_DEFAULT {\
    .spi_transfer = imu_spi_transfer, \
}

int imu_spi_transfer(void* ctx, int len, uint8_t* data_out, uint8_t* data_in);

#endif
