

#include "command.h"


COMMInstance *comm_instance;

// int Comm_init(void)
// {
//     comm_cmd_config_t comm_cmd_config = {
//         .chassis_config = {
//             .chassis_mode = NORMAL_MODE,
//             .chassis_motorsleft = {
//                 .DJImotor_config = {
//                     .rx_id = 0x202,
//                     .DJImotor_id = 2,
//                     .DJIMotor_type = M3508,
//                     .can_config = {
//                         .hcan = &hcan1,
//                         .rx_id = 0x202,
//                     },
//                 },
//                 .motor_type = DJI_MOTOR,
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,

//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_out_closeloop = SPEED_LOOP,
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_DISABLE,
//                 },
//             },
//             .chassis_motorsright = {
//                 .DJImotor_config = {
//                     .rx_id = 0x201,
//                     .DJImotor_id = 1,
//                     .DJIMotor_type = M3508,
//                     .can_config = {
//                         .hcan = &hcan1,
//                         .rx_id = 0x201,
//                     },
//                 },
//                 .motor_type = DJI_MOTOR,
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,

//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_out_closeloop = SPEED_LOOP,
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_DISABLE,
//                 },
//             },
//             .chassis_motorhright = {
//                 .DJImotor_config = {
//                     .rx_id = 0x204,
//                     .DJImotor_id = 4,
//                     .DJIMotor_type = M3508,
//                     .can_config = {
//                         .hcan = &hcan1,
//                         .rx_id = 0x204,
//                     },
//                 },
//                 .motor_type = DJI_MOTOR,
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,

//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_out_closeloop = SPEED_LOOP,
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_DISABLE,
//                 },
//             },
//             .chassis_motorhleft = {
//                 .DJImotor_config = {
//                     .rx_id = 0x203,
//                     .DJImotor_id = 3,
//                     .DJIMotor_type = M3508,
//                     .can_config = {
//                         .hcan = &hcan1,
//                         .rx_id = 0x203,
//                     },
//                 },
//                 .motor_type = DJI_MOTOR,
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,

//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_out_closeloop = SPEED_LOOP,
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_DISABLE,
//                 },
//             },
//             .chassis_mode = NORMAL_MODE,
//         },
//         .gimbal_config = {
//             .yaw_motor_config = {
//                 .DJImotor_config = {
//                     .DJImotor_id = 5,
//                     .rx_id = 0x209,
//                     .DJIMotor_type = M6020,
//                 },
//                 .motor_type = DJI_MOTOR,
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,

//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_out_closeloop = ANGLE_LOOP,
//                     .motor_closeloop_type = ANGLE_SPEED_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_DISABLE,
//                 },
//             },
//             .pitch_motor_config = {
//                 .DJImotor_config = {
//                     .DJImotor_id = 6,
//                     .rx_id = 0x20A,
//                     .DJIMotor_type = M6020,
//                 },
//                 .motor_type = DJI_MOTOR,
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,

//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_out_closeloop = ANGLE_LOOP,
//                     .motor_closeloop_type = ANGLE_SPEED_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_DISABLE,
//                 },
//             },
//         },
//         .shoot_config = {
//             .fret_motor_config = {
//                 .motor_type = DJI_MOTOR,
//                 .DJImotor_config = {
//                     .DJImotor_id = 5,
//                     .DJIMotor_type = M2006,
//                     .rx_id = 0x205,
//                 },
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                     .motor_out_closeloop = SPEED_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_source = MOTOR_FEEDSOURCE,
//                     .motor_feedback_enable_flag = MOTOR_FEEDBACK_DISABLE,

//                 },
//             },
//             .left_tiongear_config = {
//                 .motor_type = DJI_MOTOR,
//                 .DJImotor_config = {
//                     .can_config = {
//                         .hcan = &hcan1,
//                         .rx_id = 0x206,
//                     },
//                     .DJImotor_id = 6,
//                     .DJIMotor_type = M3508,
//                     .rx_id = 0x206,
//                 },
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                     .motor_out_closeloop = SPEED_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_source = MOTOR_FEEDSOURCE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                 },
//             },
//             .right_tiongear_config = {
//                 .motor_type = M3508,
//                 .DJImotor_config = {
//                     .can_config = {
//                         .hcan = &hcan1,
//                         .rx_id = 0x207,
//                     },
//                     .DJImotor_id = 7,
//                     .DJIMotor_type = M3508,
//                     .rx_id = 0x207,
//                 },
//                 .motor_pid_controller = {
//                     .angle_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .speed_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                     .current_pid = {
//                         .kp = 1,
//                         .ki = 0,
//                         .kd = 0,
//                         .Derivative_LPF_RC = 0.6,
//                         .OutPut_LPF_RC = 0.6,
//                         .ilimit = 5000,
//                         .deadline = 0,
//                         .maxout = 100000,
//                         .pid_improving = PID_INTEGRAL_LIMIT,
//                     },
//                 },
//                 .motor_pid_controlparam = {
//                     .motor_closeloop_type = SPEED_CURRENT_LOOP,
//                     .motor_out_closeloop = SPEED_LOOP,
//                 },
//                 .motor_feedback_controller = {
//                     .angle_kf = 1,
//                     .speed_kf = 1,
//                     .current_kf = 1,
//                 },
//                 .motor_feedback_param = {
//                     .motor_feedback_source = MOTOR_FEEDSOURCE,
//                     .motor_feedback_enable_flag = MOTOR_FEEDBACK_NONE,
//                     .motor_feedback_type = MOTOR_FEEDBACK_NONE,
//                 },
//             },
//         },

//     };

    

// }

COMMInstance *Comm_Regsiter(comm_cmd_config_t *_config)
{
    if (_config == NULL)
    {
        return NULL;
    }

    COMMInstance *_instance = (COMMInstance *)malloc(sizeof(COMMInstance));

    if (_instance ==NULL)

    _instance->chassis_intance = Chassis_Register(&_config->chassis_config);
    _instance->gimbal_instance = Gimbal_Register(&_config->gimbal_config);
    _instance->shoot_instance = Shoot_Register(&_config->shoot_config);
    _instance->remote_isntance = remote_register();
    _instance->comm_cmd_mode = _config->comm_cmd_mode;
    _instance->imu_instance = _instance->gimbal_instance->imu_instance;

    if (_instance->chassis_intance == NULL || _instance->gimbal_instance == NULL || _instance->imu_instance == NULL || _instance->remote_isntance == NULL || _instance->imu_instance == NULL)
    {
        return NULL; 
    }
    
    comm_instance = _instance;

    return _instance;
}

int Comm_init(void)
{
    comm_cmd_config_t comm_cmd_config = {
        .chassis_config = {
            .chassis_mode = CHASSIS_NORMAL_MODE,
            .chassis_motorsleft = {
                .DJImotor_config = {
                    .rx_id = 0x202,
                    .DJImotor_id = 2,
                    .DJIMotor_type = M3508,
                    .can_config = {
                        .hcan = &hcan1,
                        .rx_id = 0x202,
                    },
                },
                .motor_type = DJI_MOTOR,
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,

                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_out_closeloop = SPEED_LOOP,
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                },
            },
            .chassis_motorsright = {
                .DJImotor_config = {
                    .rx_id = 0x201,
                    .DJImotor_id = 1,
                    .DJIMotor_type = M3508,
                    .can_config = {
                        .hcan = &hcan1,
                        .rx_id = 0x201,
                    },
                },
                .motor_type = DJI_MOTOR,
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,

                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_out_closeloop = SPEED_LOOP,
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                },
            },
            .chassis_motorhright = {
                .DJImotor_config = {
                    .rx_id = 0x204,
                    .DJImotor_id = 4,
                    .DJIMotor_type = M3508,
                    .can_config = {
                        .hcan = &hcan1,
                        .rx_id = 0x204,
                    },
                },
                .motor_type = DJI_MOTOR,
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,

                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_out_closeloop = SPEED_LOOP,
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                },
            },
            .chassis_motorhleft = {
                .DJImotor_config = {
                    .rx_id = 0x203,
                    .DJImotor_id = 3,
                    .DJIMotor_type = M3508,
                    .can_config = {
                        .hcan = &hcan1,
                        .rx_id = 0x203,
                    },
                },
                .motor_type = DJI_MOTOR,
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,

                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_out_closeloop = SPEED_LOOP,
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                },
            },
        },
        .gimbal_config = {
            .yaw_motor_config = {
                .DJImotor_config = {
                    .DJImotor_id = 5,
                    .rx_id = 0x209,
                    .DJIMotor_type = M6020,
                },
                .motor_type = DJI_MOTOR,
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,

                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_out_closeloop = ANGLE_LOOP,
                    .motor_closeloop_type = ANGLE_SPEED_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                },
            },
            .pitch_motor_config = {
                .DJImotor_config = {
                    .DJImotor_id = 6,
                    .rx_id = 0x20A,
                    .DJIMotor_type = M6020,
                },
                .motor_type = DJI_MOTOR,
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,

                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_out_closeloop = ANGLE_LOOP,
                    .motor_closeloop_type = ANGLE_SPEED_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                },
            },
        },
        .shoot_config = {
            .fret_motor_config = {
                .motor_type = DJI_MOTOR,
                .DJImotor_config = {
                    .DJImotor_id = 5,
                    .DJIMotor_type = M2006,
                    .rx_id = 0x205,
                },
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                    .motor_out_closeloop = SPEED_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                    .motor_feedback_enable_flag = MOTOR_FEEDBACK_DISABLE,

                },
            },
            .left_tiongear_config = {
                .motor_type = DJI_MOTOR,
                .DJImotor_config = {
                    .can_config = {
                        .hcan = &hcan1,
                        .rx_id = 0x206,
                    },
                    .DJImotor_id = 6,
                    .DJIMotor_type = M3508,
                    .rx_id = 0x206,
                },
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                    .motor_out_closeloop = SPEED_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                },
            },
            .right_tiongear_config = {
                .motor_type = DJI_MOTOR,
                .DJImotor_config = {
                    .can_config = {
                        .hcan = &hcan1,
                        .rx_id = 0x207,
                    },
                    .DJImotor_id = 7,
                    .DJIMotor_type = M3508,
                    .rx_id = 0x207,
                },
                .motor_pid_controller = {
                    .angle_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .speed_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                    .current_pid = {
                        .kp = 1,
                        .ki = 0,
                        .kd = 0,
                        .Derivative_LPF_RC = 0.6,
                        .OutPut_LPF_RC = 0.6,
                        .ilimit = 5000,
                        .deadline = 0,
                        .maxout = 100000,
                        .pid_improving = PID_INTEGRAL_LIMIT,
                    },
                },
                .motor_pid_controlparam = {
                    .motor_closeloop_type = SPEED_CURRENT_LOOP,
                    .motor_out_closeloop = SPEED_LOOP,
                },
                .motor_feedback_controller = {
                    .angle_kf = 1,
                    .speed_kf = 1,
                    .current_kf = 1,
                },
                .motor_feedback_param = {
                    .motor_feedback_source = MOTOR_FEEDSOURCE,
                    .motor_feedback_enable_flag = MOTOR_FEEDBACK_DISABLE,
                    .motor_feedback_type = MOTOR_FEEDBACK_NONE,
                },
            },
        },
    };

    COMMInstance *_instance = Comm_Regsiter(&comm_cmd_config);
    
    if (_instance == NULL)
    {
        return 1;
    }

    return 0;
}