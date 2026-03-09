
#include "DJI_motor.h"

//由inputcase可知，只需要注册，电机就能完成输入

DJIMotor_Instance *DJIMotor_instances[15] = {0};
static int idx = 0;


CAN_TxHeaderTypeDef DJIMOTOR20_txhead = {
        .DLC = 0x08,
        .RTR = CAN_RTR_DATA,
        .IDE = CAN_ID_STD,
        .StdId = 0x200,                                    
};

CAN_TxHeaderTypeDef DJIMOTOR1F_txhead = {
    .DLC = 8,
    .RTR = CAN_RTR_DATA,
    .IDE = CAN_ID_STD,
    .StdId = 0x1ff,
};

CAN_TxHeaderTypeDef DJIMOTOR2F_txhead = {
    .DLC = 8,
    .RTR = CAN_RTR_DATA,
    .IDE = CAN_ID_STD,
    .StdId = 0x2ff,
};

static DJIMotor_config_t DJI_configcase = {
    .DJIMotor_type = M3508,
    .DJImotor_id = 0x01,
    .rx_id = 0x201,
    .can_config = {
        .hcan = &hcan1,
        .rx_id = 0x201,
    }
};

uint8_t tx_buffcase[8] = {11, 22, 33, 44, 55, 66, 77, 88};
uint8_t tx_buff20[8] = {0};
uint8_t tx_buff1f[8] = {0};
uint8_t tx_buff2f[8] = {0};

int rspeed_case = 0;
int current_case_in = 0;
int current_case_out = 0;

int DJIMotor_InputDcode(void *instance, uint8_t *rxdata)
{

    if (instance == NULL)
    {
        printf("DJIMotor Dcode param error\n");
        return -1;
    }

    DJIMotor_Instance *_instance = instance;
    memcpy(_instance->DJIMotor_measure.rx_buff, rxdata, 8);
    uint8_t *rx_buff = _instance->DJIMotor_measure.rx_buff;

    _instance->DJIMotor_measure.dcode = (int)((rx_buff[0] << 8) + (rx_buff[1]));
    _instance->DJIMotor_measure.rspeed = (int)((rx_buff[2] << 8) + (rx_buff[3]));
    if (_instance->DJIMotor_type == M3508)
    {
        _instance->DJIMotor_measure.rspeed /= 19.0f;
    }
    if (_instance->DJIMotor_type == M2006)
    {
        _instance->DJIMotor_measure.rspeed /= 36.0f;
    }

    _instance->DJIMotor_measure.speed = _instance->DJIMotor_measure.rspeed * radps_2_mps;
    _instance->DJIMotor_measure.current = (int)((rx_buff[4] << 8) + (rx_buff[5]));
    // _instance->DJIMotor_measure.tur_current = _instance->DJIMotor_measure.current * code_2_current;
    _instance->DJIMotor_measure.temp = (int)rx_buff[6];

    _instance->DJIMotor_measure.cur_angle = (float)(_instance->DJIMotor_measure.dcode) * DCODE_2_ANGLE; // 有待优化,确保开启了fpu

    if ((_instance->DJIMotor_measure.cur_angle - _instance->DJIMotor_measure.last_angle) < -180.0f) // 有待调整
    {
        _instance->DJIMotor_measure.turn_nb++;
    }

    if ((_instance->DJIMotor_measure.cur_angle - _instance->DJIMotor_measure.last_angle) > 180.0f)
    {
        _instance->DJIMotor_measure.turn_nb--;
    }

    _instance->DJIMotor_measure.toltal_angle = (_instance->DJIMotor_measure.turn_nb * AROUND_ANGLE) + _instance->DJIMotor_measure.cur_angle;
    _instance->DJIMotor_measure.last_angle = _instance->DJIMotor_measure.cur_angle;

    //调试用参数，正常应注释
    rspeed_case = _instance->DJIMotor_measure.rspeed;
    current_case_in = _instance->DJIMotor_measure.current;
    
    return 0;
}


int DJIMotor_Output_Init(can_config_t *config)
{
    return 0;
}

int DJIMotor_settxbuff(void)
{
    for(int i = 0;i < idx;i++)
    {
        if (DJIMotor_instances[i] == NULL) return -1;
        if (DJIMotor_instances[i]->DJIMotor_type == M3508)
        {
            if (DJIMotor_instances[i]->DJImotor_id <= 4)
            {
                int tx_ptr = DJIMotor_instances[i]->DJImotor_id * 2 - 2;
                tx_buff20[tx_ptr] = (int)DJIMotor_instances[i]->ref >> 8;
                tx_buff20[tx_ptr + 1] = (int)DJIMotor_instances[i]->ref;
                current_case_out = (tx_buff20[tx_ptr] << 8) + tx_buff20[tx_ptr + 1];
            }
            if (DJIMotor_instances[i]->DJImotor_id > 4)
            {
                int tx_ptr = DJIMotor_instances[i]->DJImotor_id * 2 - 10;
                tx_buff1f[tx_ptr] = (int)DJIMotor_instances[i]->ref >> 8;
                tx_buff1f[tx_ptr + 1] = (int)DJIMotor_instances[i]->ref;
            }
                
        }
        if (DJIMotor_instances[i]->DJIMotor_type == M2006)
        {
            if (DJIMotor_instances[i]->DJImotor_id <= 4)
            {
                int tx_ptr = DJIMotor_instances[i]->DJImotor_id * 2 - 2;
                tx_buff20[tx_ptr] = (int)DJIMotor_instances[i]->ref >> 8;
                tx_buff20[tx_ptr + 1] = (int)DJIMotor_instances[i]->ref;
            }
            if (DJIMotor_instances[i]->DJImotor_id > 4)
            {
                int tx_ptr = DJIMotor_instances[i]->DJImotor_id * 2 - 10;                
                tx_buff1f[tx_ptr] = (int)DJIMotor_instances[i]->ref >> 8;
                tx_buff1f[tx_ptr + 1] = (int)DJIMotor_instances[i]->ref;
            }
        }
        if (DJIMotor_instances[i]->DJIMotor_type == M6020)
        {
            if (DJIMotor_instances[i]->DJImotor_id <= 4)
            {
                int tx_ptr = DJIMotor_instances[i]->DJImotor_id * 2 - 2;
                tx_buff1f[tx_ptr] = (int)DJIMotor_instances[i]->ref >> 8;
                tx_buff1f[tx_ptr + 1] = (int)DJIMotor_instances[i]->ref;
            }
            if (DJIMotor_instances[i]->DJImotor_id > 4)
            {
                int tx_ptr = DJIMotor_instances[i]->DJImotor_id * 2 - 10;
                tx_buff2f[tx_ptr] = (int)DJIMotor_instances[i]->ref >> 8;       
                tx_buff2f[tx_ptr + 1] = (int)DJIMotor_instances[i]->ref;
            }
        }
    }
    return 0;
}

int DJIMotor_Sendassis(void)
{
    if (DJIMotor_settxbuff() != 0)
    {
        return -1;
    }
    Can_TxAssist(&hcan1, &DJIMOTOR20_txhead, tx_buff20);
    Can_TxAssist(&hcan1, &DJIMOTOR1F_txhead, tx_buff1f);
}

int DJIMotor_sendcase(void)
{

    if (Can_TxAssist(&hcan1, &DJIMOTOR20_txhead, tx_buffcase) != 0)
    {
        printf("DJI sendcase error\n");
        return -1;
    }
    return 0;
}



DJIMotor_Instance *DJIMotor_Register(DJIMotor_config_t *_config)
{
    if(_config == NULL)
    {
        printf("DJImotor Register errror\n");
        return NULL;
    }

    DJIMotor_Instance *_instance = (DJIMotor_Instance *)malloc(sizeof(DJIMotor_Instance));
    if (_instance == NULL)
    {
        printf("DJIMotor instance error\n");
        return NULL;
    }

    _instance->DJImotor_id = _config->DJImotor_id;
    _instance->DJIMotor_type = _config->DJIMotor_type;
    _instance->rx_id = _config->rx_id;

    _instance->can_instance = Can_Register(&_config->can_config);
    _instance->can_instance->_instance = (void *)_instance;
    _instance->can_instance->can_dcode = DJIMotor_InputDcode;

    DJIMotor_instances[idx++] = _instance;

    return _instance;
}

int DJIMotor_inputcase(void)
{
    DJIMotor_Instance *_instance = DJIMotor_Register(&DJI_configcase);
    

    return 0;
}

int DJIMotor_Output(void)
{

    return 0;
}




