#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "main.h"
#include "motor.h"
#include "arm_math.h"
#include "imu.h"

#define DEGREE_2_RAD 57.2957795131f
#define radius 0.150f 
#define RAD_PS_2_RPM (30.0f / pi)


typedef enum
{
    CHASSIS_NORMAL_MODE = 0,
 
}chassis_mode_e;

typedef struct chassis_config_s
{
    motor_config_t chassis_motorsleft;
    motor_config_t chassis_motorsright;
    motor_config_t chassis_motorhleft;
    motor_config_t chassis_motorhright;

    chassis_mode_e chassis_mode;
}chassis_config_t;


typedef struct 
{

    Motor_Instance *chassis_motorsleft;
    Motor_Instance *chassis_motorsright;
    Motor_Instance *chassis_motorhleft;
    Motor_Instance *chassis_motorhright;
    
    chassis_mode_e chassis_mode;

    float vx;
    float vy;
    float gim_vx;
    float gim_vy;
    float wz;
    float dri_angle;
}ChassisInstance;

ChassisInstance *Chassis_Register(chassis_config_t *_config);

#endif // !







