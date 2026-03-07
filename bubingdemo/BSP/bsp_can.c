#include "bsp_can.h"

CANInstance *can_instances[CANINSTANCE_NB] = {0};
static int idx = 0;

int Can_Start(void)
{
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000; 
    can_filter_st.FilterBank = 0;
    // can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterFIFOAssignment = CAN_FilterFIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
    return 0;
}

// void MycanInit(void)
// {

//     HAL_StatusTypeDef status;
//     do
//     {
//         status = HAL_CAN_Start(&hcan1); // 启动CAN
//         if (status != HAL_OK)
//         {
//             HAL_Delay(100); // 延迟后重试
//         }
//     } while (status != HAL_OK);

//     CAN_FilterTypeDef filter_Init;
//     filter_Init.FilterActivation = ENABLE;
//     filter_Init.FilterBank = 0;
//     filter_Init.FilterFIFOAssignment = CAN_RX_FIFO0;
//     filter_Init.FilterIdHigh = 0x0000;
//     filter_Init.FilterIdLow = 0x0000;
//     filter_Init.FilterMaskIdHigh = 0x0000;
//     filter_Init.FilterMaskIdLow = 0x0000;
//     filter_Init.FilterMode = CAN_FILTERMODE_IDMASK;
//     filter_Init.FilterScale = CAN_FILTERSCALE_16BIT;
//     filter_Init.SlaveStartFilterBank = 14;

//     HAL_CAN_ConfigFilter(&hcan1, &filter_Init);
//     HAL_CAN_Start(&hcan1);
//     HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
// }


int Can_CallBack(CAN_HandleTypeDef *hcan, uint32_t fifox)
{
    if(hcan == NULL) return -1;
    uint8_t rx_data[CANBUFFER_LENGTH] = {0};
    CAN_RxHeaderTypeDef rx_header = {0};
    
    HAL_CAN_GetRxMessage(hcan, fifox, &rx_header, rx_data);

    for(int i = 0;i < idx;i++)
    {
        if(rx_header.StdId == can_instances[i]->rx_id)
        {
            if(can_instances[i]->can_dcode(can_instances[i]->_instance, rx_data) != 0)
            {
                printf("can dcode error\n");
                return 1;
            }
            return 0;
        }
    }
    return 2; 
    
    
}

int Can_Dcodedemo(CANInstance *_instance, uint8_t *rxdata)
{

    if (_instance == NULL || rxdata == NULL) return -1;


    for (int i = 0;i < CANBUFFER_LENGTH;i++)
    {
        _instance->can_txdata[i] = arm_sin_f32(rxdata[i]);
    }

    if (_instance->can_txmessage(_instance) != 0)
    {
        printf("can tx error\n");
        return 1;
    }

    return 0;

}


int Can_TxMessage(CANInstance *_instance)
{
    if (_instance == NULL) return -1;

    if (HAL_CAN_AddTxMessage(_instance->hcan, &(_instance->tx_header), _instance->can_txdata, &_instance->send_mail_box) != HAL_OK)
    {
        printf("hal can rx error\n");
        return 1;
    }
    return 0;
}

int Can_TxAssist( CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *tx_header, uint8_t *tx_buff)
{
    if (tx_buff == NULL)
    {
        printf("can txassist param error\n");
        return -1;
    }
    
    uint32_t send_mail_box = 0;

    if (HAL_CAN_AddTxMessage(hcan, tx_header, tx_buff, &send_mail_box) != HAL_OK)
    {
        printf("hal can rx error\n");
        return 1;
    }
    return 0;
}

CANInstance *Can_Register(can_config_t *_config)
{

    if(_config == NULL) return NULL;

    CANInstance *can_instance = (CANInstance *)malloc(sizeof(CANInstance));
    if(can_instance == NULL) return NULL;
    memset(can_instance, 0, sizeof(CANInstance));

    can_instance->hcan = _config->hcan;
    can_instance->rx_id = _config->rx_id;
    can_instance->tx_header.DLC = _config->tx_header.DLC;
    can_instance->tx_header.IDE = _config->tx_header.IDE;
    can_instance->tx_header.RTR = _config->tx_header.RTR;
    can_instance->tx_header.StdId = _config->tx_header.StdId;
    can_instance->tx_header.TransmitGlobalTime = _config->tx_header.TransmitGlobalTime;

    can_instance->can_callback = Can_CallBack;    
    can_instance->can_txmessage = Can_TxMessage;

    can_instances[idx++] = can_instance;
    return can_instance;

}

int can_textcase(void)
{
    can_config_t can1_config = {
        .hcan = &hcan1,
        .rx_id = 0x201,
        .tx_header = {
            .DLC = 8,
            .IDE = CAN_ID_STD,
            .RTR = CAN_RTR_DATA,
            .StdId = 0x200,
        }
    };
    can_config_t can2_config = {
//        .hcan = &hcan2,
        .rx_id = 0x202,
        .tx_header = {
            .DLC = 8,
            .IDE = CAN_ID_STD,
            .RTR = CAN_RTR_DATA,
            .StdId = 0x200,
        }
    };

    CANInstance *can1_instance = Can_Register(&can1_config);
    CANInstance *can2_instance = Can_Register(&can2_config);
//    can1_instance->can_dcode = Can_Dcodedemo;
//    can2_instance->can_dcode = Can_Dcodedemo;
    return 0;

}



void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if(Can_CallBack(hcan, CAN_RX_FIFO0) != 0)
    {
        printf("can callback error\n");
        return;
    }
}




// void CAN_cmd_gimbal(void)
// {
//     static CAN_TxHeaderTypeDef gimbal_tx_message;
//     static uint8_t gimbal_can_send_data[8];
//     uint32_t send_mail_box = 0;
//     gimbal_tx_message.StdId = 0x200;
//     gimbal_tx_message.IDE = CAN_ID_STD;
//     gimbal_tx_message.RTR = CAN_RTR_DATA;
//     gimbal_tx_message.DLC = 0x08;
//     gimbal_can_send_data[0] = (1 >> 8);
//     gimbal_can_send_data[1] = 1;
//     gimbal_can_send_data[2] = (2 >> 8);
//     gimbal_can_send_data[3] = 2;
//     gimbal_can_send_data[4] = (3 >> 8);
//     gimbal_can_send_data[5] = 3;
//     gimbal_can_send_data[6] = (4 >> 8);
//     gimbal_can_send_data[7] = 4;
//     HAL_CAN_AddTxMessage(&hcan1, &gimbal_tx_message, gimbal_can_send_data, (uint32_t *)CAN_TX_MAILBOX0);
// }

// void CanMotorTransmit(uint16_t id, int16_t v1, int16_t v2, int16_t v3, int16_t v4)
// {
//     uint8_t tx_data[8];
//     CAN_TxHeaderTypeDef tx_header;
//     tx_header.IDE = CAN_ID_STD;
//     tx_header.RTR = CAN_RTR_DATA;
//     tx_header.StdId = id;
//     tx_header.DLC = 8;
//     tx_data[0] = (v1 >> 8) & 0xff;
//     tx_data[1] = (v1) & 0xff;
//     tx_data[2] = (v2 >> 8) & 0xff;
    
//     tx_data[3] = (v2) & 0xff;
    
//     tx_data[4] = (v3 >> 8) & 0xff;
    
//     tx_data[5] = (v3) & 0xff;
    
//     tx_data[6] = (v4 >> 8) & 0xff;
    
//     tx_data[7] = (v4) & 0xff;
    
//     HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data, (uint32_t *)CAN_TX_MAILBOX0);
// }