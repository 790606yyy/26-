

#include "bsp_usart.h"

uart_instance_t *uart_instances[MAX_UART_INSTANCE];
static int idx;

static uint8_t uart1_rx[MAX_BUFFER_LENGTH];
static uint8_t uart3_rx[MAX_BUFFER_LENGTH];

int Uart_Dma_Trans(UART_HandleTypeDef *huart, uint8_t * txbuffer, uint16_t length)
{   
    if (txbuffer == NULL || length == 0 || huart == NULL) return -1;

    if (HAL_UART_Transmit_DMA(huart, txbuffer, length) != HAL_OK)
    {
        printf("hal uart dma tx error\n");
        return 1;
    }

    return 0;

}

int Uart_Trans(UART_HandleTypeDef *huart, uint8_t *txbuffer, uint16_t length)
{
    if (txbuffer == NULL || length == 0 || huart == NULL) return -1;

    if (HAL_UART_Transmit(huart, txbuffer, length, 50) != HAL_OK)
    {
        printf("hal uart dma tx error\n");
        return 1;
    }

    return 0;
}



int Uart_dcode(uint8_t *rxbuffer, uint16_t length)
{

    if (rxbuffer == NULL || length == 0) return 1;


    return 0;
}



int Uart_Dma_RxMsg(UART_HandleTypeDef *huart, uint8_t *rxbuffer, uint16_t maxlength)
{
    if(huart == NULL || rxbuffer == NULL || maxlength == 0) return -1;

    if (HAL_UARTEx_ReceiveToIdle_DMA(huart, rxbuffer, maxlength) != HAL_OK)
    {
//        printf("hal uart rxmsg error\n");
        return 1;
    }
    __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
    return 0;
}

int Uart_RxMsg(UART_HandleTypeDef *huart, uint8_t *rxbuffer, uint16_t maxlength)
{
    return 0;
}


int Uart_Dma_Callback(UART_HandleTypeDef *huart)
{

    if(huart == NULL) return -1;

    uint32_t DMA_FLAGS3, tmp3;
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    {
        tmp3 = huart->Instance->SR;
        tmp3 = huart->Instance->DR;  
        tmp3++;
        DMA_FLAGS3 = __HAL_DMA_GET_TC_FLAG_INDEX(huart->hdmarx);
        __HAL_DMA_DISABLE(huart->hdmarx);
        __HAL_DMA_CLEAR_FLAG(huart->hdmarx, DMA_FLAGS3);

        huart->hdmarx->Instance->NDTR = huart->RxXferSize;
        __HAL_DMA_ENABLE(huart->hdmarx);
    }
    else 
        return 1;

    for (int i = 0;i < idx;i++)
    {
        if (huart == uart_instances[i]->huart)
        {
            if (uart_instances[i]->uart_dcode(uart_instances[i]->instance ,uart_instances[i]->rx_buffer, 128) != 0)
            {
//                printf("uart dcode error\n");
                return 2;
            }

            if (uart_instances[i]->uart_rxmsg(uart_instances[i]->huart, uart_instances[i]->rx_buffer, uart_instances[i]->max_rx_length) != 0)
            {
//                printf("uart rxmag error\n");
                return 3;
            }

            return 0;
        
        }
    }

    return 4;

}

int Uart_CallBack()
{

}

void HAL_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart)
{

    if(huart == NULL) return;

    if (Uart_Dma_Callback(huart) != 0)
    {
//        printf("uart callback error\n");
        return ;
    }

        
}




uart_instance_t *UART_Regiser(uart_config_t *_config)
{
    if (_config == NULL) return NULL;

    uart_instance_t *_instance = (uart_instance_t *)malloc(sizeof(uart_instance_t));
    if (_instance == NULL)
    {
        printf("uart_instance malloc error\n");
        return NULL;
    }
    memset(_instance, 0, sizeof(uart_instance_t));

    
    _instance->max_rx_length = _config->max_rx_length;
    _instance->uart_mod = _config->uart_mod;
    _instance->huart = _config->huart;
    _instance->uart_dcode = _config->uart_dcode;
    _instance->instance = _config->_instance;
    if (_instance->huart == &huart1)
    {
        _instance->rx_buffer = uart1_rx;
    }
    if (_instance->huart == &huart3)
    {
        _instance->rx_buffer = uart3_rx;
    }

    if (_instance->uart_mod == NOEMAL_MOD)
    {
        _instance->uart_trans = Uart_Trans;
        _instance->uart_rxmsg = Uart_RxMsg;
    }

    if (_instance->uart_mod == DMA_MOD)
    {
        _instance->uart_trans = Uart_Dma_Trans;
        _instance->uart_rxmsg = Uart_Dma_RxMsg;
        _instance->uart_callback = Uart_Dma_Callback;
    }
    
    _instance->uart_rxmsg(_instance->huart, _instance->rx_buffer, 128);

    uart_instances[idx ++] = _instance;
    return _instance;
  
}






