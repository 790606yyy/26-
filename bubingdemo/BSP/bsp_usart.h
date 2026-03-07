#ifndef BSP_USART_H
#define BSP_USART_H

#include "main.h"
#include "usart.h"

#define MAX_BUFFER_LENGTH   128
#define MAX_UART_INSTANCE   10

typedef int (*UART_CALLBACK)(UART_HandleTypeDef *);
typedef int (*UART_Dcode)(void *,uint8_t *, uint16_t);
typedef int (*UART_Trans)(UART_HandleTypeDef *, uint8_t *, uint16_t);
typedef int (*UART_RxMEG)(UART_HandleTypeDef *, uint8_t *, uint16_t);


typedef enum 
{
    NOEMAL_MOD = 0,
    DMA_MOD,
} uart_mod_e;


typedef struct uart_config_s
{

    uart_mod_e uart_mod;
    UART_HandleTypeDef *huart;
    uint16_t max_rx_length;
    UART_Dcode uart_dcode;
    void *_instance;

}uart_config_t;


typedef struct uart_instance_s
{
    
    uart_mod_e uart_mod;
    UART_HandleTypeDef *huart;
    uint16_t buffer_length;

    uint16_t max_rx_length;    
    uint16_t rx_idx;
    uint16_t rx_length;
    uint8_t *rx_buffer;
    uint8_t *tx_buffer;

    UART_CALLBACK uart_callback;
    UART_Dcode uart_dcode;
    UART_Trans uart_trans;
    UART_RxMEG uart_rxmsg;
    void *instance;
}uart_instance_t;

uart_instance_t *UART_Regiser(uart_config_t *_config);
void HAL_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart);

#endif // !BSP_USART_H
