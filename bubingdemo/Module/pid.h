
#ifndef PID_H
#define PID_H

//请确保开启了fpu,stmf4系列fpu不支持双精度浮点数加速

#include "main.h"

typedef enum 
{
    PID_IMPROVE_NONE = 0x000000,
    PID_INTEGRAL_LIMIT = 0x000001,
    
}pid_improving_e;


typedef struct 
{
    float kp;
    float ki;
    float kd;
    float kf;

    float pout;
    float iout;
    float iterm;
    float dout;

    float ilimit;
    float maxout;
    float deadline;
    
    float output;
    float lastout;
    float lastpout;
    float lastiout;
    float lastdout;
    float lastiterm;
    float lasterror;

    float last_measure;
    float measure;
    float ref;
    float error;

    float OutPut_LPF_RC;
    float Derivative_LPF_RC;
    float dt;

    pid_improving_e pid_improving;

}PID_Instance;

float pid_calculate(PID_Instance *_instance, float measure);

#endif // !PID_H
