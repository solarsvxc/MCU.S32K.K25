#include "DriverHeader/Driver_Common.h"
#include "DriverHeader/Driver_Port.h"

#define PORT_MAX_PINS           32U
#define PORT_IS_AVAILABLE(n)     ((n) < PORT_MAX_PINS)
// MUX per port
void PORTx_MuxControl( PORT_Type *port_module, Type_PortMux mux,uint8_t pin){
    port_module->PCR[PORT_IS_AVAILABLE(pin)] |= PORT_PCR_MUX(mux); 
}
// PCC CGC enable
void PORTx_PCC_Enable(uint16_t pcc_portx_index){
    IP_PCC->PCCn[pcc_portx_index] |= PCC_PCCn_CGC_MASK;
}
// PCC CGC disable
void PORTx_PCC_Disable(uint16_t pcc_portx_index){
    IP_PCC->PCCn[pcc_portx_index] |= PCC_PCCn_CGC_MASK;
}



