#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

#include <stdint.h>

// 16-byte IMU register map
extern uint8_t imu_mem[16];

// acc range
#define ACC_MIN -32768
#define ACC_MAX  32767

// gyro range
#define GYRO_MIN -32768
#define GYRO_MAX  32767

// IMU register definitions
#define IMU_CTRL_REG (*(volatile uint16_t *)(imu_mem + 0x00))
#define ACC_X (*(volatile int16_t *)(imu_mem + 0x02))
#define ACC_Y (*(volatile int16_t *)(imu_mem + 0x04))
#define ACC_Z (*(volatile int16_t *)(imu_mem + 0x06))

#define GYRO_X (*(volatile int16_t *)(imu_mem + 0x08))
#define GYRO_Y (*(volatile int16_t *)(imu_mem + 0x0A))
#define GYRO_Z (*(volatile int16_t *)(imu_mem + 0x0c))

// control register masks
enum CtrlBits
{
    CTRL_START_BIT = 0,
    CTRL_STOP_BIT = 1,
    CTRL_RESET_BIT = 2,
    CTRL_INT_BIT = 3,
};

#define CTRL_START (1 << CTRL_START_BIT)
#define CTRL_STOP (1 << CTRL_STOP_BIT)
#define CTRL_RESET (1 << CTRL_RESET_BIT)
#define CTRL_INT (1 << CTRL_INT_BIT)
#define CTRL_FREQ_MASK 0xFFF

// structure to hold acc and gyro readings
typedef struct
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
} imu_data_t;

// function definitions
void imu_init(uint16_t freq);
void imu_read(imu_data_t *data);
void imu_handle_interrupt(void);

#endif