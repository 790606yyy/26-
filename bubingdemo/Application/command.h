#ifndef __COMMAND_H
#define __COMAND_H

#include "remote.h"
#include "imu.h"
#include "chassis.h"
#include "gimbal.h"
#include "shoot.h"

typedef enum
{

    NORMAL_MODE = 0,
    AUTO_MODE = 1,
}comm_cmd_mode_e;

typedef struct comm_cmd_config_s 
{
    chassis_config_t  chassis_config;
    gimbal_config_t   gimbal_config;
    shoot_config_t shoot_config;
    comm_cmd_mode_e comm_cmd_mode;  

}comm_cmd_config_t;


typedef struct 
{

    comm_cmd_mode_e comm_cmd_mode;
    
    IMUInstance *imu_instance;
    Remote_Instance *remote_isntance;
    ChassisInstance *chassis_intance;
    GIMBALInstance *gimbal_instance;
    ShootInstance *shoot_instance;
    

}COMMInstance;

COMMInstance *Comm_Regsiter(comm_cmd_config_t *_config);
int Comm_init(void);

#endif // !