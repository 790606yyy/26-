#ifndef __IMU_H
#define __IMU_H

#include "main.h"
#include "bsp_usart.h"

#define pi 3.1415926535f
#define rad_2_degree 180.0f/pi


typedef struct imu_measure_s 
{
    float rollSpeed;
    float pitchSpeed;
    float yawSpeed;
    float roll;
    float pitch;
    float yaw;
    float qw;
    float qy;
    float qz;
    float timetamp;

}imu_measure_t;

typedef struct 
{

    imu_measure_t imu_measure;
    uart_instance_t *uart_instance;
}IMUInstance;

IMUInstance *IMU_Init(void);

#endif // !__IMU_H
