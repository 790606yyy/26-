#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"
#include "bsp_usart.h"
#include "usart.h"


typedef union key_s
{
    struct 
    {
        uint16_t w : 1;
        uint16_t s : 1;
        uint16_t a : 1;
        uint16_t d : 1;
        uint16_t shift : 1;
        uint16_t ctrl : 1;
        uint16_t q : 1;
        uint16_t e : 1;
        uint16_t r : 1;
        uint16_t f : 1;
        uint16_t g : 1;
        uint16_t z : 1;
        uint16_t x : 1;
        uint16_t c : 1;
        uint16_t v : 1;
        uint16_t b : 1;
    }key;
    uint16_t key_nb;

}key_u;



typedef struct remote_data_s
{
    struct 
    {
        uint16_t channel0;
        uint16_t channel1;
        uint16_t channel2;
        uint16_t channel3;

        uint8_t s1;
        uint8_t s2;

 
    }rc;

    struct 
    {
        int32_t x;
        int32_t y;
        int32_t z;  
        
        uint8_t mouse_left;
        uint8_t mouse_right;
        key_u key;
    }mouse;


}remote_data_t;



typedef struct 
{
    uint32_t rx_buff;
    remote_data_t remote_data;
    
    uart_instance_t *uart_instance;

}Remote_Instance;

Remote_Instance *remote_register(void);

#endif // !__REMOTE_H




