#ifndef DJI_MOTOR_H
#define DJI_MOTOR_H

// #include "motor.h"
#include "bsp_can.h"

#define DCODE_2_ANGLE (360.0f / 8191.0f)
#define AROUND_ANGLE 360.0f


//typedef enum
//{
//    M2006 = 0,
//    M3508 = 1,
//    M6020 = 2
//}DJIMotor_type_e;

typedef enum {
    M2006 = 0,
    M3508 = 1,
    M6020 = 2
} DJIMotor_type_e;

typedef struct DJIMotor_measure_s
{
    
    float cur_angle;
    int rspeed;
    int current;
                                
    int temp;
    int turn_nb;
    int dcode;
    float toltal_angle;
    float last_angle;
                                                                                           
    uint8_t rx_buff[8];

}DJIMotor_measure_t;

typedef struct DJIMotor_config_s
{
    DJIMotor_type_e DJIMotor_type;
    int DJImotor_id;
    int rx_id;

    can_config_t can_config;

}DJIMotor_config_t;

typedef struct 
{
    DJIMotor_type_e DJIMotor_type;
    // motor_pid_controller_t motor_pid_controller;
    // motor_pid_controlparam_t motor_pid_controlparam;

    DJIMotor_measure_t DJIMotor_measure;
    int DJImotor_id;
    int rx_id;

    CANInstance *can_instance;
    
    float ref;
 
}DJIMotor_Instance;

DJIMotor_Instance *DJIMotor_Register(DJIMotor_config_t *_config);
int DJIMotor_sendcase(void);
int DJIMotor_inputcase(void);


#endif // !