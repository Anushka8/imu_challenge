# Intertial Measurement Unit (IMU)

## Project Structure

### `/imu_challenge` - Source Code
- **`main.c`**: Test cases simulating the behavior of IMU
- **`imu_driver.c`**: Main IMU logic
- **`imu_driver.h`**: Register and function definitons
- **`CMakeLists.txt`**: CMake build script


## Build Instructions

### Prerequisites
- GCC or Clang
- CMake 3.10+
- Linux, macOS, or WSL (for `usleep()`)

### Build

```
mkdir build && cd build
cmake ..
make
./imu_challenge
```
OR

```
gcc -o imu_test main.c imu_driver.c
./imu_test
```

### Sample Output
```
Waking up....
Logging accelerometer & gyroscope readings.
[INTERRUPT] Accel: -81 -45 63 | Gyro: 30 -96 -43
[INTERRUPT] Accel: -13 -76 -36 | Gyro: -42 21 32
[INTERRUPT] Accel: -44 -38 87 | Gyro: -2 -39 74
[INTERRUPT] Accel: 35 -66 -100 | Gyro: -17 59 72
[INTERRUPT] Accel: -42 -90 57 | Gyro: -63 -6 -76
Turning off 
[SKIP] IMU is OFF. Ignoring interrupt.
```

## Module Breakdown
### **`imu_driver.h`**
- Contains a dummy memory register that simulates an IMU register map
- Definitions for registers
- Data structure to read accelerometer and gyroscope values
- Function definitions for IMU behavior
- Range definitions for `ACC` and `GYRO`. For now the range is defined as -32767 to 32767. This can be changed depending on the actual acceptable range.

### **`imu_driver.c`**
- Function imeplementation
- Incoming accelerometer and gyroscope value validation using `clamp` function
- Interrup handler

### **`main.c`**
- Starts the "device"
- Generates random values for sensors
- Emulates interrupt behavior by setting `INT` bit to 1
- Stops the "device"

## Assumptions & Limitations
- Sensor values are generated using `rand()`. In real world, other factors like sensitivity of the sensors, noice, etc will have to considered.
- Interrupt is simulated by manually setting the `INT`, whereas in real system, it will be automatically set by IMU hardware and triggering ISR.

