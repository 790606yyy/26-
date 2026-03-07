#ifndef __MOTOR_H
#define __MOTOR_H

#include "pid.h"
#include "main.h"
#include "DJI_motor.h"
#include "42_motor.h"
#include "DM_motor.h"

typedef enum 
{
    DJI_MOTOR = 0,
    DM_MOTOR = 1,
    F42_MOTOR = 2,
}motor_type_e;

typedef enum
{
    OPEN_LOOP = 0x0000,
    ANGLE_LOOP = 0x0001,
    SPEED_LOOP = 0x0010,
    CURRENT_LOOP = 0x0100,

    ANGLE_SPEED_LOOP = 0x0110,
    SPEED_CURRENT_LOOP = 0x0011,
    ALL_LOOP = 0x0111,

}motor_closeloop_type_e;

typedef enum
{
    MOTOR_FEEDSOURCE = 0,
    OTHER_FEEDSOURCE = 1,
}motor_feedback_source_e;

typedef enum
{
    MOTOR_FEEDBACK_NONE = 0x0000,
    MOTOR_ANGLE_FEEDBACK = 0x0001,
    MOTOR_SPEED_FEEDBACK = 0x0010,
    MOTOR_CURRENT_FEEDBACK = 0x0100
}motor_feedback_type_e;

typedef enum 
{
    MOTOR_RESERVE_NONE = 0,
    MOTOR_RESERVE_ON = 1,
}motor_reserveflag_e;

typedef enum
{
    MOTOR_FEEDBACK_RESERVE_NONE = 0,
    MOTOR_FEEDBACK_RESERVE_ON = 1,

}motor_feedback_reserveflag_e;

typedef enum
{
    MOTOR_ENABLE = 0,
    MOTOR_DISABLE = 1
}motor_enable_e;

typedef enum
{
    MOTOR_FEEDBACK_DISABLE = 0,
    MOTOR_FEEDBACK_ENABLE = 1
}motor_feedback_enable_e;

typedef struct motor_pid_controlparam_s
{
    motor_closeloop_type_e motor_out_closeloop;
    motor_closeloop_type_e motor_closeloop_type;

} motor_pid_controlparam_t;

typedef struct motor_pid_controller_s
{
    
    PID_Instance angle_pid;
    PID_Instance speed_pid;
    PID_Instance current_pid;

}motor_pid_controller_t;


typedef struct motor_feedback_s
{
    float *other_angle_sfeedback_ptr;
    float *other_speed_sfeedback_ptr;
    float *angle_sfeedback_ptr;
    float *speed_sfeedback_ptr;  
    float *current_sfeedback_ptr;

    float angle_kf;
    float speed_kf;
    float current_kf;
}motor_feedback_controller_t;

                                                         
typedef struct motor_feedback_param_s
{
    motor_feedback_type_e motor_feedback_type;
    motor_feedback_source_e motor_feedback_source;
    motor_feedback_reserveflag_e motor_feedback_reserveflag;
    motor_feedback_enable_e motor_feedback_enable_flag;

}motor_feedback_param_t;



typedef struct motor_config_s
{
    motor_type_e motor_type;

    motor_pid_controller_t motor_pid_controller;
    motor_pid_controlparam_t motor_pid_controlparam;
    motor_feedback_param_t motor_feedback_param;
    motor_feedback_controller_t motor_feedback_controller;

    motor_reserveflag_e motor_reserveflag;
    motor_enable_e motor_enable_flag;

    DJIMotor_config_t DJImotor_config;
    F42Motor_config_t F42motor_config;
    DMMotor_config_t DMmotor_config;

}motor_config_t;

typedef struct 
{
    motor_type_e motor_type;

    motor_pid_controller_t motor_pid_controller;
    motor_pid_controlparam_t motor_pid_controlparam;
    motor_feedback_param_t motor_feedback_param;
    motor_feedback_controller_t motor_feedback_controller;
    
    motor_reserveflag_e motor_reserveflag;
    motor_enable_e motor_enable_flag;

    DJIMotor_Instance *DJI_instance;
    F42Motor_Instance *F42_Instance;
    DMMotor_Instance *DM_Instance
}Motor_Instance;

Motor_Instance *Motor_Register(motor_config_t *_config);
Motor_Instance *Motor_Registercase(void);

#endif // !__MOTOR_H



