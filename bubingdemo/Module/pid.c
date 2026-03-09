
#include "pid.h"

void Pid_IntegralLimit(PID_Instance *_Instance)
{
    if (_Instance->ilimit == 0)
    {
        printf("ilimit is noinit\n");
        return;
    }
    if (_Instance->iout > _Instance->ilimit)
    {
        _Instance->iout = _Instance->ilimit;
    }
    if (_Instance->iout < -_Instance->ilimit)
    {
        _Instance->iout = -_Instance->ilimit;
    }

}

void Pid_OutPut_LPC_RC(PID_Instance *_Instance)
{
    if (_Instance->OutPut_LPF_RC == 0)
    {
        printf("OutPut_LPF_RC is no init\n");
        return;
    }

    _Instance->output = _Instance->output * _Instance->OutPut_LPF_RC + _Instance->lastout * (1 - _Instance->OutPut_LPF_RC);

}

void Pid_DeadLine(PID_Instance *_Instance)
{
    if (_Instance->deadline == 0)
    {
        return;
    }
    if (_Instance->output > 0 && _Instance->output < _Instance->deadline)
    {
        _Instance->output = 0;
    }
    if (_Instance->output < 0 && _Instance->output > -_Instance->deadline) 
    {
        _Instance->output = 0;
    }
}

void Pid_OutLimited(PID_Instance *_instance)
{
    if (_instance->maxout == 0) return;

    if (_instance->output > _instance->maxout)
    {
        _instance->output = _instance->maxout;
    }

    if (_instance->output < - _instance->maxout)
    {
        _instance->output = - _instance->maxout;
    }

}

float pid_calculate(PID_Instance *_instance, float measure)
{

    if (_instance == NULL)
    {
        printf("pid_instance error\n");
        return -1.0f;
    }

    _instance->error = _instance->ref - measure;
    _instance->pout = (_instance->kp) * (_instance->error);
    _instance->dout = (_instance->kd) * (_instance->error - _instance->lasterror);
    _instance->iterm = (_instance->ki) * (_instance->error);
    _instance->iout += _instance->iterm;

    if (_instance->pid_improving & PID_INTEGRAL_LIMIT)
    {
        Pid_IntegralLimit(_instance);
    }

    _instance->output = _instance->pout + _instance->dout + _instance->iout;

    

    Pid_OutPut_LPC_RC(_instance);

    Pid_DeadLine(_instance);

    Pid_OutLimited(_instance);

    _instance->lastpout = _instance->pout;
    _instance->lastiout = _instance->iout;
    _instance->lastiterm = _instance->iterm;
    _instance->lastdout = _instance->dout;
    _instance->lastout = _instance->output;
    _instance->lasterror = _instance->error;

    return _instance->output;
}


