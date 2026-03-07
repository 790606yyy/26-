
#include "42_motor.h"


F42Motor_Instance *F42Motor_Register(F42Motor_config_t *_config)
{
    if (_config == NULL)
    {
        printf("42motor instance error\n");
        return NULL;
    }
    F42Motor_Instance *_instance = (F42Motor_Instance *)malloc(sizeof(F42Motor_Instance));
    if (_instance == NULL)
    {
        printf("F42Motor instance malloc error\n");
        return NULL;
    }


    return _instance;
}



