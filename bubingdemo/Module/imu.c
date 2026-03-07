
#include "imu.h"


IMUInstance *imu_instances[3] = {0};
static int idx;


float char_2_float(uint8_t Data_1, uint8_t Data_2, uint8_t Data_3, uint8_t Data_4)
{
    long long transition_32;
    float tmp = 0;
    float last_tmp = 0;
    int sign = 0;
    int exponent = 0;
    float mantissa = 0;
    transition_32 = 0;
    transition_32 |= Data_4 << 24; // 得到数据的底 8 位
    transition_32 |= Data_3 << 16;
    transition_32 |= Data_2 << 8;
    transition_32 |= Data_1;                      // 得到数据的高 8 位
    sign = (transition_32 & 0x80000000) ? -1 : 1; // 符号位
    // 先右移操作，再按位与计算，出来结果是 30 到 23 位对应的 e
    exponent = ((transition_32 >> 23) & 0xff) - 127;
    // 将 22~0 转化为 10 进制，得到对应的 x 系数
    mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
    tmp = sign * mantissa * pow(2, exponent);
    last_tmp = tmp;
    return tmp;
}

int IMU_Dcode(void *instance, uint8_t *rxbuffer, uint16_t length)
{

    if (instance == NULL || rxbuffer == NULL || length == 0)
    {
        printf("imu dcode param error\n");
        return -1;
    }
    IMUInstance *_instance = (IMUInstance *)instance;

    _instance->imu_measure.yaw = char_2_float(rxbuffer[27], rxbuffer[28], rxbuffer[29], rxbuffer[30]);
    _instance->imu_measure.yawSpeed = char_2_float(rxbuffer[15], rxbuffer[16], rxbuffer[17], rxbuffer[18]);
    _instance->imu_measure.pitch = char_2_float(rxbuffer[23], rxbuffer[24], rxbuffer[25], rxbuffer[26]);

    return 0;

}

IMUInstance *IMU_Init(void)
{

    uart_config_t imu_uart_config = {
        .huart = &huart1,
        .max_rx_length = 80,
        .uart_dcode = IMU_Dcode,
        .uart_mod = DMA_MOD,
    };
    IMUInstance *_instance = (IMUInstance *)malloc(sizeof(IMUInstance));
    memset(_instance, 0, sizeof(IMUInstance));

    imu_uart_config._instance = _instance;

    _instance->uart_instance = UART_Regiser(&imu_uart_config);
    if (_instance->uart_instance == NULL)
    {
        printf("imu uart init error\n");
        return NULL;
    }
    
    imu_instances[idx++] = _instance;

    return _instance;
}



