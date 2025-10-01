/**
 * @file main.c
 * @author duongnn (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "S32K144.h"

#define POTENTIOMETER_C 14
#define BLUE_D           0
#define GREEN_D    16
#define RED_D      15

/**
 * @brief 
 * 
 * @return 
 */
int main(void)
{

    /*<! SOSCDIV1_CLK 8Mhz
    * System OSC Clock Divide 1 Clock divider 1 for System OSC
    * 001 Divide by 1 
    */
    IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1);

    /*<! SOSCDIV2_CLK 8Mhz
    * System OSC Clock Divide 2 Clock divider 2 for System OSC
    * 001 Divide by 1 
    */
    IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV2(1);
    /* Range=2: Medium freq (SOSC betw 1MHz-8MHz) 	*/
    /* HGO=0:   Config xtal osc for low power 		*/
    /* EREFS=1: Input is external XTAL 			*/
    IP_SCG->SOSCCFG  = SCG_SOSCCFG_RANGE(2);
    IP_SCG->SOSCCFG |= SCG_SOSCCFG_EREFS(1);

    while(IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); 	/* Ensure SOSCCSR unlocked */
    IP_SCG->SOSCCSR = SCG_SOSCCSR_SOSCEN_MASK; 
    
    /*<======================ADC0-Init===========================>*/

    /* Disable clock to change PCS */
    IP_PCC->PCCn[PCC_ADC0_INDEX] &=~ PCC_PCCn_CGC_MASK;
    /* PCS=1: Select SOSCDIV2 		*/
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1);     
    /* Enable bus clock in ADC 	*/
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;  

    /* ADCH=1F: Module is disabled for conversions	*/
    IP_ADC0->SC1[0] |= ADC_SC1_ADCH_MASK;

    /* CFG1 MODE = 00b -> 10 bit conversion */
    /* ADIV = 00b -> input by rate clock */
    /* ADICLK = 00b -> ALTCLK 1 */
    IP_ADC0->CFG1   = ADC_CFG1_ADIV(0) | ADC_CFG1_ADICLK(0) | ADC_CFG1_MODE(3);
    
    /* SMPLTS default */
    IP_ADC0->CFG2   = ADC_CFG2_SMPLTS(0xC);

    IP_ADC0->SC2    = 0x00000000;
    IP_ADC0->SC3    = 0x00000000;


    /*<======================GPIO-PORT Init===========================>*/
    /*<! Disable CGC on PORTC */
    IP_PCC->PCCn[PCC_PORTC_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Enable CGC on PORTC */
    IP_PCC->PCCn[PCC_PORTC_INDEX]  |= PCC_PCCn_CGC_MASK;
    /*<! Disable CGC on PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Disable CGC on PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX]  |= PCC_PCCn_CGC_MASK;

    // IP_PORTC->PCR[POTENTIOMETER_C]    = PORT_PCR_MUX(0);

    IP_PORTD->PCR[GREEN_D]            = PORT_PCR_MUX(1);
    IP_PORTD->PCR[BLUE_D]             = PORT_PCR_MUX(1);
    IP_PORTD->PCR[RED_D]              = PORT_PCR_MUX(1);

    IP_PTD->PDDR    				   |= (1U<<BLUE_D) | (1U<<GREEN_D) | (1U<<RED_D);
    IP_PTD->PSOR                        |= (1U<<GREEN_D) | (1U<<BLUE_D) | (1U<<RED_D);

    /* Check SC1[0] value at sequence 0 compare with ADC_SC1_COCO_MASK <value at bit number 8 of register SC1>
    *  Then shift right value compared 
    */
    
    while (1)
    {
        volatile uint16_t result_in_mv = 0;
        /* Initiate new conversion by writing to ADC0_SC1A(ADCH) */
        /* ADCH = 12: External channel 12 as input */
        IP_ADC0->SC1[0] |= ADC_SC1_ADCH(12);
        
        while((uint8_t)((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT)== 0); // sw break hear !!!!!!!!

        result_in_mv =(uint32_t) ((IP_ADC0->SC1[0] * 3300)/0x3FFU); // 0 -> 1023, 2^n - 1

        if ( 0 <  result_in_mv && result_in_mv <= 341 )
        {
            IP_PTD->PTOR   = (1U<<RED_D);
        } else if (341 < result_in_mv && result_in_mv <= 682)
        {
            IP_PTD->PTOR   = (1U<<BLUE_D);

        } else if ( 682 < result_in_mv && result_in_mv <= 1023)
        {
            IP_PTD->PTOR   = (1U<<GREEN_D);
        }

        /* DELAY function */
        for (uint8_t i = 0; i < 100; i++){}
    }
}

