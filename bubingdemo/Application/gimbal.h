#ifndef __GIMBAL_H
#define __GIMBAL_H


#include "imu.h"
#include "motor.h"
typedef struct gimbal_config_s 
{
    motor_config_t yaw_motor_config;
    motor_config_t pitch_motor_config;
     
}gimbal_config_t;


typedef struct
{
    
    Motor_Instance *yaw_motor;
    Motor_Instance *pitch_motor; 
    IMUInstance *imu_instance;

    float gimbal_pitchDegree;
    float gimbal_yawDegree;

} GIMBALInstance;

GIMBALInstance *Gimbal_Register(gimbal_config_t *_config);
 
#endif // !