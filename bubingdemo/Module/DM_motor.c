#include "DM_motor.h"

DMMotor_Instance *DMMotor_Register(DMMotor_config_t *_config)
{
    if (_config == NULL)
    {
        printf("DMmotor instance error\n");
        return NULL;
    }
    DMMotor_Instance *_instance = (DMMotor_Instance *)malloc(sizeof(DMMotor_Instance));
    if (_instance == NULL)
    {
        printf("DMMotor instance malloc error\n");
        return NULL;
    }

    return _instance;
}