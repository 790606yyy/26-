

#include "motor.h"

Motor_Instance *motor_instances[15] = {0};
static int idx = 0;

DJIMotor_config_t DJI_configcase = {
    .DJIMotor_type = M3508,
    .DJImotor_id = 0x01,
    .rx_id = 0x201,
    .can_config = {
        .hcan = &hcan1,
        .rx_id = 0x201,
    }
};

motor_config_t motor_configcase = {
          .motor_type = DJI_MOTOR,
          .motor_enable_flag = MOTOR_ENABLE,
          .motor_reserveflag = MOTOR_RESERVE_NONE,
          .motor_pid_controller = {
              .angle_pid = {
                  .kp = 1,
                  .ki = 0,
                  .kd = 0,
                  .Derivative_LPF_RC = 0,
                  .OutPut_LPF_RC = 0.6,
                  .deadline = 0,
                  .ilimit = 1000,
                  .pid_improving = PID_INTEGRAL_LIMIT,
                  .maxout = 100000,
                  .ref = 100,
              },
              .speed_pid = {
                  .kp = 1,
                  .ki = 0,
                  .kd = 0,
                  .Derivative_LPF_RC = 0,
                  .OutPut_LPF_RC = 0.6,
                  .deadline = 0,
                  .ilimit = 1000,
                  .pid_improving = PID_INTEGRAL_LIMIT,
                  .maxout = 100000,
                  .ref = 100,
              },
              .current_pid = {
                  .kp = 1,
                  .ki = 0,
                  .kd = 0,
                  .Derivative_LPF_RC = 0,
                  .OutPut_LPF_RC = 0.6,
                  .deadline = 0,
                  .ilimit = 1000,
                  .pid_improving = PID_INTEGRAL_LIMIT,
                  .maxout = 100000,
                  .ref = 100,
              },
          },
          .motor_pid_controlparam = {
            .motor_closeloop_type = SPEED_CURRENT_LOOP,
            .motor_out_closeloop = SPEED_LOOP,
          },
          .motor_feedback_controller = {
            .speed_kf = 1,
            .angle_kf = 1,
            .current_kf = 1,
          },
          .motor_feedback_param = {
            .motor_feedback_type = MOTOR_SPEED_FEEDBACK,
            .motor_feedback_source = MOTOR_FEEDSOURCE
          },
          .DJImotor_config = {
                .DJIMotor_type = M3508,
                .DJImotor_id = 0x01,
                .rx_id = 0x201,
                .can_config = {
                    .hcan = &hcan1,
                    .rx_id = 0x201,
                }
          }
        };

Motor_Instance *Motor_Register(motor_config_t * _config)
{
    if(_config == NULL)
    {
        printf("motor register error\n");
        return NULL;
    }
    Motor_Instance *_instance = (Motor_Instance *)malloc(sizeof(Motor_Instance));
    if (_instance == NULL)
    {
        printf("motor instance malloc error");
        return NULL;
    }
    
    _instance->motor_type = _config->motor_type;
    _instance->motor_enable_flag  = _config->motor_enable_flag;
    _instance->motor_reserveflag = _config->motor_reserveflag;

    memcpy(&_instance->motor_pid_controller, &_config->motor_pid_controller, sizeof(motor_pid_controller_t));
    memcpy(&_instance->motor_pid_controlparam, &_config->motor_pid_controlparam, sizeof(motor_pid_controlparam_t));
    memcpy(&_instance->motor_feedback_controller, &_config->motor_feedback_controller, sizeof(motor_feedback_controller_t));
    memcpy(&_instance->motor_feedback_param, &_config->motor_feedback_param, sizeof(motor_feedback_param_t));
    // _instance->type_instance = (void *)DJIMotor_Register();

    if (_instance->motor_type == DJI_MOTOR)
    {
        _instance->DJI_instance = DJIMotor_Register(&(_config->DJImotor_config));
    }

    motor_instances[idx++] = _instance;

    return _instance;
}

Motor_Instance *Motor_Registercase(void)
{
    if (&motor_configcase == NULL)
    {
        printf("motor register error\n");
        return NULL;
    }
    Motor_Instance *_instance = (Motor_Instance *)malloc(sizeof(Motor_Instance));
    if (_instance == NULL)
    {
        printf("motor instance malloc error");
        return NULL;
    }

    _instance->motor_type = motor_configcase.motor_type;
    _instance->motor_enable_flag = motor_configcase.motor_enable_flag;
    _instance->motor_reserveflag = motor_configcase.motor_reserveflag;

    memcpy(&_instance->motor_pid_controller, &motor_configcase.motor_pid_controller, sizeof(motor_pid_controller_t));
    memcpy(&_instance->motor_pid_controlparam, &motor_configcase.motor_pid_controlparam, sizeof(motor_pid_controlparam_t));
    memcpy(&_instance->motor_feedback_controller, &motor_configcase.motor_feedback_controller, sizeof(motor_feedback_controller_t));
    memcpy(&_instance->motor_feedback_param, &motor_configcase.motor_feedback_param, sizeof(motor_feedback_param_t));
    // _instance->type_instance = (void *)DJIMotor_Register();

    if (_instance->motor_type == DJI_MOTOR)
    {
        _instance->DJI_instance = DJIMotor_Register(&(motor_configcase.DJImotor_config));
    }

    motor_instances[idx++] = _instance;

    return _instance;
}
