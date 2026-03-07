#ifndef __DM_MOTOR_H
#define __DM_MOTOR_H

#include "main.h"

typedef struct DMMotor_config_s
{
    int DM_id;
} DMMotor_config_t;

typedef struct
{
    int dm_id;
} DMMotor_Instance;

DMMotor_Instance *DMMotor_Register(DMMotor_config_t *_config);

#endif // !