cmake_minimum_required(VERSION 3.10)
project(imu_challenge)

set(CMAKE_C_STANDARD 11)

add_executable(imu_challenge
    main.c
    imu_driver.c
)