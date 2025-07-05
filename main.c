#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  
#include "imu_driver.h"

uint8_t imu_mem[16];

void simulate_imu_data_and_interrupt() {
    IMU_CTRL_REG |= CTRL_INT;

    // set register values for accelerometer
    *(int16_t*)(imu_mem + 0x02) = rand() % 200 - 100;  
    *(int16_t*)(imu_mem + 0x04) = rand() % 200 - 100;
    *(int16_t*)(imu_mem + 0x06) = rand() % 200 - 100;
    
    // set register values for gyroscope
    *(int16_t*)(imu_mem + 0x08) = rand() % 200 - 100;  
    *(int16_t*)(imu_mem + 0x0A) = rand() % 200 - 100;
    *(int16_t*)(imu_mem + 0x0C) = rand() % 200 - 100;
    
}

int main() {
    srand(time(NULL));  
    // TURN ON THE DEVICE 
    printf("Waking up....\n"); 
    imu_init(100);          // initialize with 100 Hz
    usleep(100000); 

    // HANDLE INTERRUPTS
    printf("Logging accelerometer & gyroscope readings.\n");
    for (int i = 0; i < 5; ++i) {
        simulate_imu_data_and_interrupt(); 
        imu_handle_interrupt();            
        usleep(200000);                    // wait 200ms
    }

    // TURN OFF THE DEVICE
    printf("Turning off \n");
    IMU_CTRL_REG &= ~CTRL_START;

    // INTERRUPT SHOULD NOT BE TRIGGERED WHEN DEVICE IS OFF
    simulate_imu_data_and_interrupt();
    imu_handle_interrupt();

    return 0;
}
