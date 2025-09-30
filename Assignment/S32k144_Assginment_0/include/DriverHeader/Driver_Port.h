#ifndef DRIVERHEADER_DRIVER_PORT_H_
#define DRIVERHEADER_DRIVER_PORT_H_

#include "S32K144.h" 

typedef enum 
{
    PORT_MUX_DISABLED = 0,
    PORT_MUX_GPIO     = 1,
    PORT_MUX_ALT2     = 2,
    PORT_MUX_ALT3     = 3,
    PORT_MUX_ALT4     = 4,
    PORT_MUX_ALT5     = 5,
    PORT_MUX_ALT6     = 6,
    PORT_MUX_ALT7     = 7,
} Type_PortMux;

void PORTx_MuxControl(PORT_Type *port_module, Type_PortMux mux,uint8_t pin);
void PORTx_PCC_Enable(uint32_t port_index);
void PORTx_PCC_Disable(uint32_t port_index);


#endif /* DRIVERHEADER_DRIVER_PORT_H_ */
