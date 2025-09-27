/**
 * @file main.c
 * @author duongnn
 * @brief
 * @version 0.1
 * @date 2025-09-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "S32K144.h"   // CMSIS header cho S32K144

#define BLUE     0
#define GREEN    16
#define RED      15

/* Found this information: https://developer.arm.com/documentation/dui0552/a/cortex-m3-peripherals/system-timer--systick */
#define SYST_CSR                (*(uint32_t *)(0xE000E010UL))                   /*!< SysTick Control and Status Register         */
#define SYST_RVR                (*(uint32_t *)(0xE000E014UL))                   /*!< SysTick Reload Value Register               */
#define SYST_CVR                (*(uint32_t *)(0xE000E018UL))                   /*!< SysTick Current Value Register              */
/*By default, the frequency of the MCU S32K144 is 16Mhz in 1ms*/
#define CTRL_ENABLE             (1U<<0)                                         /*!<    */
#define CTRL_CLCKSRC            (1U<<2)                                         /*!<    */
#define CTRL_COUNTFLAG          (1U<<16)                                        /*!<    */

/**
 * @brief
 *
 * @param delayms
 * @param one_msec_load
 */
static void delay_ms(uint32_t delayms)
{
    SYST_RVR = 48000 - 1;
    SYST_CVR = 0;
    SYST_CSR =  CTRL_CLCKSRC;
    SYST_CSR |= CTRL_ENABLE;
    // delay function
    for (unsigned int i = 0; i < delayms; i++)
    {
        while ((SYST_CSR & CTRL_COUNTFLAG) == 0);
    }
}

int main(void)
{

    IP_PCC->PCCn[PCC_PORTD_INDEX] &= ~PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTD_INDEX] |=  PCC_PCCn_CGC_MASK;

    IP_PORTD->PCR[BLUE]             = PORT_PCR_MUX(1);
    IP_PORTD->PCR[RED]              = PORT_PCR_MUX(1);
    IP_PORTD->PCR[GREEN]            = PORT_PCR_MUX(1);
    
    while (1)
    {
    IP_PTD->PDDR                 = (1U<<BLUE); 
    delay_ms(3000);
    IP_PTD->PDDR                 = (1U<<GREEN);
    delay_ms(3000);
    IP_PTD->PDDR                 = (1U<<RED);
    delay_ms(3000);
    }
    
}
