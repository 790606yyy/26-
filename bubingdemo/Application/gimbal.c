#include "gimbal.h"

GIMBALInstance *gimbal_instance;

GIMBALInstance *Gimbal_Register(gimbal_config_t *_config)
{
    if (_config == NULL)
    {
        return NULL;
    } 
    
    GIMBALInstance *_instance = (GIMBALInstance *)malloc(sizeof(GIMBALInstance));
    if (_instance == NULL) 
    {
        return NULL;
    }
    
    _instance->imu_instance = IMU_Init(); 
    _instance->yaw_motor = Motor_Register(&_config->yaw_motor_config);
    _instance->pitch_motor = Motor_Register(&_config->pitch_motor_config);

    if (_instance->imu_instance == NULL || _instance->yaw_motor == NULL || _instance->pitch_motor == NULL)
    {
        return NULL;
    }

    gimbal_instance = _instance;

    return _instance;
} 



