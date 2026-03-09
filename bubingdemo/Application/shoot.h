#ifndef __SHOOT_H
#define __SHOOT_H

#include "motor.h"
 
typedef struct shoot_config_s
{

    motor_config_t fret_motor_config; 
    motor_config_t left_tiongear_config;
    motor_config_t right_tiongear_config;
}shoot_config_t;

typedef struct
{
    Motor_Instance *fret_motor; 
    Motor_Instance *left_tiongear;
    Motor_Instance *right_tiongear;
 
} ShootInstance;

ShootInstance *Shoot_Register(shoot_config_t *_config);

#endif // !
