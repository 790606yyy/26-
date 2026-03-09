

#include "chassis.h"
#include "arm_math.h"
ChassisInstance *chassis_instance = NULL;
// Motor_Instance *chassis_motors[4] = {0};

ChassisInstance *Chassis_Register(chassis_config_t *_config)
{

    ChassisInstance *_instance = (ChassisInstance *)malloc(sizeof(ChassisInstance));
    if (_instance == NULL)
    {
        return NULL;
    }

    _instance->chassis_motorhleft = Motor_Register(&_config->chassis_motorsleft);
    _instance->chassis_motorhright = Motor_Register(&_config->chassis_motorsright);
    _instance->chassis_motorsleft = Motor_Register(&_config->chassis_motorhleft);
    _instance->chassis_motorsright = Motor_Register(&_config->chassis_motorhright);

    if (_instance->chassis_motorhleft == NULL || _instance->chassis_motorhright == NULL || _instance->chassis_motorsleft == NULL || _instance->chassis_motorsright == NULL)
    {
        return NULL;
    }
    _instance->chassis_mode = _config->chassis_mode;

    chassis_instance = _instance;

    return _instance;
}
      
static void OMNICALCULATE()
{
    // 右前轮
    chassis_instance->chassis_motorsright->ref = -(RAD_PS_2_RPM) * (1 / radius) * (-chassis_instance->vx + chassis_instance->vy + chassis_instance->wz);
    // 左前轮
    chassis_instance->chassis_motorsleft->ref = -(RAD_PS_2_RPM) * (1 / radius) * (chassis_instance->vx + chassis_instance->vy + chassis_instance->wz);
    // 左后轮
    chassis_instance->chassis_motorhleft->ref = -(RAD_PS_2_RPM) * (1 / radius) * (chassis_instance->vx - chassis_instance->vy + chassis_instance->wz);
    // 右后轮
    chassis_instance->chassis_motorhright->ref = -(RAD_PS_2_RPM) * (1 / radius) * (-chassis_instance->vx - chassis_instance->vy + chassis_instance->wz);
}
 
int Chassis_Gimthe_2_Chathe(void)
{
    if (chassis_instance == NULL)
    {
        return -1;
    }

    float cos_theta = (float)arm_cos_f32(chassis_instance->dri_angle * DEGREE_2_RAD);
    float sin_theta = (float)arm_sin_f32(chassis_instance->dri_angle * DEGREE_2_RAD);

    chassis_instance->vx = chassis_instance->gim_vx * cos_theta - chassis_instance->gim_vy * sin_theta;
    chassis_instance->vy = chassis_instance->gim_vx * sin_theta + chassis_instance->gim_vy * cos_theta;
     
}


int Chassis_Task(void)
{
    
    
    
}




