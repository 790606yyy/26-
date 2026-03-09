#ifndef DJI_MOTOR_H
#define DJI_MOTOR_H

// #include "motor.h"
#include "bsp_can.h"
#include "main.h"
#define DCODE_2_ANGLE (360.0f / 8191.0f)
#define AROUND_ANGLE 360.0f
#define tyre_len 0.152f
#define radps_2_mps 0.0079587f
#define code_2_current 0.0012207f

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
    int16_t rspeed;
    float speed;
    int16_t current;
    float tur_current;
                                
    int8_t temp;
    int turn_nb;
    uint16_t dcode;
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
int DJIMotor_Sendassis(void);
int DJIMotor_settxbuff(void);
#endif // !