 
#include "remote.h"

static uint16_t temp[10] = {0};
static uint16_t vx;
static uint16_t vy;
static uint16_t vz;
#define REMOTE_MAX_INSTANCE 5
Remote_Instance *remote_instances[REMOTE_MAX_INSTANCE] = {0};
static int idx = 0;


//初步实现遥控器调试，键鼠未经测试

int remote_dcode(void *_instance, uint8_t *rxbuffer, uint16_t length)
{
    // if(rxbuffer == NULL || length == 0)
    // {
    //     printf("remote dcode error\n");
    //     return -1;
    // }
    Remote_Instance *remote_instance = (Remote_Instance *)_instance;

    remote_instance->remote_data.rc.channel0 = ((int16_t)rxbuffer[0] | ((int16_t)rxbuffer[1] << 8)) & 0x07FF;
    remote_instance->remote_data.rc.channel1 = (((int16_t)rxbuffer[1] >> 3) | ((int16_t)rxbuffer[2] << 5)) & 0x07FF;
    remote_instance->remote_data.rc.channel2 = (((int16_t)rxbuffer[2] >> 6) | ((int16_t)rxbuffer[3] << 2) |
                                                ((int16_t)rxbuffer[4] << 10)) &
                                               0x07FF;
    remote_instance->remote_data.rc.channel3 = (((int16_t)rxbuffer[4] >> 1) | ((int16_t)rxbuffer[5] << 7)) &
                                               0x07FF;

    remote_instance->remote_data.rc.s1 = ((rxbuffer[5] >> 4) & 0x000C) >> 2;
    remote_instance->remote_data.rc.s2 = ((rxbuffer[5] >> 4) & 0x0003);

    remote_instance->remote_data.mouse.x = ((int16_t)rxbuffer[6]) | ((int16_t)rxbuffer[7] << 8); // 鼠标左右动（右为正）
    temp[0] = ((int16_t)rxbuffer[6]) | ((int16_t)rxbuffer[7] << 8);
    vx = temp[0];
    remote_instance->remote_data.mouse.y = ((int16_t)rxbuffer[8]) | ((int16_t)rxbuffer[9] << 8); // 鼠标上下动（下为正）
    temp[1] = ((int16_t)rxbuffer[8]) | ((int16_t)rxbuffer[9] << 8);
    vy = temp[1];
    remote_instance->remote_data.mouse.z = ((int16_t)rxbuffer[10]) | ((int16_t)rxbuffer[11] << 8); // 鼠标滚轮上下动（上为正）
    temp[2] = ((int16_t)rxbuffer[10]) | ((int16_t)rxbuffer[11] << 8);
    vz = temp[2];
    remote_instance->remote_data.mouse.mouse_left = rxbuffer[12];
    temp[3] = rxbuffer[12];
    remote_instance->remote_data.mouse.mouse_right = rxbuffer[13];
    temp[4] = rxbuffer[13];
    remote_instance->remote_data.mouse.key.key_nb = (uint16_t)((rxbuffer[14]) | (rxbuffer[15] << 8));
    temp[5] = (uint16_t)((rxbuffer[14]) | (rxbuffer[15] << 8));

    // memset(rxbuffer, 0, length);
    return 0;
}


uart_config_t uart_config = {
    .huart = &huart3,
    .uart_dcode = remote_dcode,
    .uart_mod = DMA_MOD,
    .max_rx_length = 128,
};



Remote_Instance *remote_register(void)
{
    Remote_Instance *_instance = malloc(sizeof(Remote_Instance));
    if(_instance == NULL)
    {
        printf("remote error\n");
        return NULL;
    }
    uart_config._instance = (void *)_instance;

    memset(_instance, 0, sizeof(Remote_Instance));

    _instance->uart_instance = UART_Regiser(&uart_config);

    
    remote_instances[idx++] = _instance;

    return _instance;
}







