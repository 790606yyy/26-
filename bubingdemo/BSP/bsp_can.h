#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "main.h"
#include "can.h"

#define CANBUFFER_LENGTH     8
#define CANINSTANCE_NB       20





typedef struct can_config_s
{
    uint16_t rx_id;
    CAN_HandleTypeDef *hcan;
    CAN_TxHeaderTypeDef tx_header;
    
}can_config_t;

typedef struct can_instance_s
{
    uint16_t rx_id;
    CAN_HandleTypeDef *hcan;
    CAN_TxHeaderTypeDef tx_header;
    
    uint8_t can_txdata[CANBUFFER_LENGTH];
    uint32_t send_mail_box;
    int (*can_callback)(CAN_HandleTypeDef *, uint32_t);
    int (*can_dcode)(void *_instances, uint8_t *rx_buff);
    int (*can_txmessage)(struct can_instance_s *);
    void *_instance;
}CANInstance;



int can_textcase(void);
CANInstance *Can_Register(can_config_t *_config);
int Can_Start(void);
int Can_TxAssist(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *tx_header, uint8_t *tx_buff);
//void CAN_cmd_gimbal(void);
//void CanMotorTransmit(uint16_t id, int16_t v1, int16_t v2, int16_t v3, int16_t v4);
// void MycanInit(void);

#endif // !BSP_CAN_H
