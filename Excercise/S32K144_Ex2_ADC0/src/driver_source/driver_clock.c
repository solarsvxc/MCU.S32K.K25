/*
 * driver_clock.c
 *
 *  Created on: 30 Sept 2025
 *      Author: DUONG
 */
#include "driver_header/driver_clock.h"

/**
 * @brief 
 * 
 */
void init_SOSC_8MHz(void)
{
    /*System OSC Clock Divide 1 
    * System OSC Clock Divide 2  Divide by 1 */
    IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
    
    /* External Reference Select  //    0 External reference clock selected  
    * High Gain Oscillator Select //    1 Configure crystal oscillator for high-gain operation
    * System OSC Range Select     //    10 Medium frequency range selected for the crytstal oscillator
    */
    IP_SCG->SOSCCFG = SCG_SOSCCFG_EREFS(0) | SCG_SOSCCFG_HGO(1) | SCG_SOSCCFG_RANGE(0x10); 

    /* Check this register can write ? */
    while (IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);

    /* System OSC Enable */
    IP_SCG->SOSCCSR     = SCG_SOSCCSR_SOSCEN(1);

    /* Wait OSC clk valid
    * Why need valid ?
    * Beacause The SOSC is considered valid after 4096 xtal counts. */
    while(!(IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));
}

