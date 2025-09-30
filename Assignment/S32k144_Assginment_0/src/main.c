/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "S32K144.h"
#include "DriverHeader/Driver_Port.h"

#define RED 0
#define BLUE 16
#define GREEN 15


int main(void)
{
    PORTx_PCC_Disable(PCC_PORTD_INDEX);
    PORTx_PCC_Enable(PCC_PORTD_INDEX);

    PORTx_MuxControl(IP_PORTD,PORT_MUX_GPIO,RED);
    PORTx_MuxControl(IP_PORTD,PORT_MUX_GPIO,BLUE);
    PORTx_MuxControl(IP_PORTD,PORT_MUX_GPIO,GREEN);
    
    //TODO: setup gpio,


}