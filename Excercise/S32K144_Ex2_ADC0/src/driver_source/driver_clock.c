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

    /* Wait OSC CLK valid
    * Why need valid ?
    * Because The SOSC is considered valid after 4096 XTAL counts. */
    while(!(IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));
}
void init_SPLL_160Mhz(void)
{
    /* System PLL is not enabled or clock is not valid 
    * (IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) return 1 when its valid 
    *  
    * 
    * */
    while ((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK));
    
    /*SPLLEN disable !Must do before configure SPLLCSR*/
    IP_SCG->SPLLCSR     = SCG_SPLLCSR_SPLLEN(0);

    /*SPLLDIV1 divide by 2 */
    IP_SCG->SPLLDIV     = SCG_SPLLDIV_SPLLDIV1(2);
    /*SPLLDIV2 divide by 4 */
    IP_SCG->SPLLDIV     |= SCG_SPLLDIV_SPLLDIV1(3);

}
