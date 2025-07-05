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
[INTERRUPT] Accel: 29 -100 30 | Gyro: -87 75 36
[INTERRUPT] Accel: -32 5 41 | Gyro: -28 37 -13
[INTERRUPT] Accel: 26 -99 27 | Gyro: -26 -22 -64
[INTERRUPT] Accel: 52 -72 -52 | Gyro: 23 -67 35
[INTERRUPT] Accel: -42 -20 -17 | Gyro: 23 -38 -77
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

## Assumptions 
- The assumption is that frequency values are mapped 1:1 as to Hz, there is a serial logger to log messages.
- Wait time is added for simulation. This is not required in real scenario.
- Setting `RESET` bit to 1 clears all memory mapped values (the device is OFF)

## Limitations
- Can add `gtest` to unit test IMU. 
- Can add error handlers for frequency range.
- Sensor values are generated using `rand()`. In real world, other factors like sensitivity of the sensors, noise, etc will have to considered.
- Interrupt is simulated by manually setting the `INT`, whereas in real system, it will be automatically set by IMU hardware and triggering ISR.
- `START` and `STOP` bits are not utilized

## Usage
- Robotic Arm (DUH!): Both sensors can help stabilize hand movements. By defining specific actions (holding a large or a small object), the system can calliberate and adjust hand motions to suit each task.
- Wireless earphone: To detect "In-ear" action by the user. Although an optic sensor is also used, the accelerometer detects how fast the earbud moves to confirm actions.

