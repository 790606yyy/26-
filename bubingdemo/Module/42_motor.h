#ifndef __42_MOTOR_H
#define __42_MOTOR_H

#include "main.h"


typedef struct F42Motor_config_s
{
    int f42_id;
}F42Motor_config_t;


typedef struct 
{
    int f42_id;
}F42Motor_Instance;

F42Motor_Instance *F42Motor_Register(F42Motor_config_t *_config);

#endif // !


