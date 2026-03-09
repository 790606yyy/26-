

#include "shoot.h"

ShootInstance *shoot_instance; 

ShootInstance *Shoot_Register(shoot_config_t *_config)
{

    if (_config == NULL)
    {
        return NULL;
    }

    ShootInstance *_instance = (ShootInstance *)malloc(sizeof(ShootInstance));

    _instance->fret_motor = Motor_Register(&_config->fret_motor_config);
    _instance->left_tiongear = Motor_Register(&_config->left_tiongear_config);
    _instance->right_tiongear = Motor_Register(&_config->right_tiongear_config);

    if (_instance->fret_motor == NULL || _instance->left_tiongear == NULL || _instance->right_tiongear == NULL)
    {
        return NULL;
    }

    shoot_instance = _instance; 

    return _instance;

}

