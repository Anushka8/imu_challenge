#include "imu_driver.h"
#include <stdio.h>

void imu_init(uint16_t freq)
{
    // if freq is greater than 12-bit value, set it to max 12-bit value
    // frequency value is 1:1 with Hz
    IMU_CTRL_REG = ((freq & CTRL_FREQ_MASK) << 4) | CTRL_START;
}

static int16_t clamp(int16_t val, int16_t min, int16_t max) {
    if (val > max) {
        return max;
    } else if (val < min) {
        return min;
    }
    return val;
}

void imu_read(imu_data_t *data)
{
    data->ax = clamp(ACC_X, ACC_MIN, ACC_MAX);
    data->ay = clamp(ACC_Y, ACC_MIN, ACC_MAX);
    data->az = clamp(ACC_Z, ACC_MIN, ACC_MAX);
    data->gx = clamp(GYRO_X, GYRO_MIN, GYRO_MAX);
    data->gy = clamp(GYRO_Y, GYRO_MIN, GYRO_MAX);
    data->gz = clamp(GYRO_Z, GYRO_MIN, GYRO_MAX);
}

void imu_handle_interrupt(void)
{
    // if the device is reset, don't trigger the interupt
    if (IMU_CTRL_REG & CTRL_RESET) {
        printf("[SKIP] IMU is OFF. Ignoring interrupt.\n");
        return;
    }

    if (IMU_CTRL_REG & CTRL_INT)
    {
        imu_data_t data;
        imu_read(&data);
        printf("[INTERRUPT] Accel: %d %d %d | Gyro: %d %d %d\n",
               data.ax, data.ay, data.az, data.gx, data.gy, data.gz);
        IMU_CTRL_REG &= ~CTRL_INT; // Clear INT bit after read
    }
}