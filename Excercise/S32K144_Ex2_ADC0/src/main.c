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

#define POTENTIOMETER_C 14
#define BLUE_D     0
#define GREEN_D    16
#define RED_D      15

uint32_t ADC_rawResult;
uint16_t ADC_mvResult;


/**
 * @brief 
 * 
 * @return int 
 */
int main(void)
{


    static int range1 = 0;
    static int range2 = 341;
    static int range3 = 682;
    static int range4 = 1024;
    /*<! Disable bus clock to set clock source PCS */
    IP_PCC->PCCn[PCC_ADC0_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Peripheral Clock Source Select,  011b Clock option 3 is FIRCDIV2_CLK*/
    IP_PCC->PCCn[PCC_ADC0_INDEX]  = PCC_PCCn_PCS(3);
    /* Enable bus clock in ADC */
    IP_PCC->PCCn[PCC_ADC0_INDEX]  =  PCC_PCCn_CGC_MASK;
    /* FIRCDIV2 = 4: FIRCDIV2 divide by 8 */
    IP_SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(4);
    /* CAL = 1: Start calibration sequence */
    /* AVGE = 1: Enable hardware average */
    /* AVGS = 11b: 32 samples averaged */
    IP_ADC0->SC3 = ADC_SC3_CAL_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);  
    
    /* Wait for completion conversion */
    while(((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT) == 0);
    
    /* ADC0 Channel 12, 10 bit resolution*/
    /*<======================ADC0 init===========================>*/
    /*<! ADCH disable for conversion*/
    IP_ADC0->SC1[0]     = ADC_SC1_ADCH_MASK;
    /*<! ADIV = 0 The divide ratio is 1 and the clock rate is input clock.
         MODE = 1: 10-bit conversion */
    IP_ADC0->CFG1       = ADC_CFG1_ADIV(2) | ADC_CFG1_MODE(2);
    /*<! Sample time is 13 ADC clks*/
    IP_ADC0->CFG2       = ADC_CFG2_SMPLTS(12);
    /*<! Conversion Trigger Select chose = 0 Software trigger*/
    IP_ADC0->SC2        = ADC_SC2_ADTRG(0);
    /* ADCO = 0: One conversion performed */
    /* AVGE,AVGS = 0: HW average function disabled */
    IP_ADC0->SC3        =0x00000000; 

    /*<======================GPIO-PORT===========================>*/
   /*<! Disable CGC on PORTC */
    IP_PCC->PCCn[PCC_PORTC_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Enable CGC on PORTC */
    IP_PCC->PCCn[PCC_PORTC_INDEX]  = PCC_PCCn_CGC_MASK;
    /*<! Disable CGC on PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Disable CGC on PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX]  = PCC_PCCn_CGC_MASK;


    IP_PORTC->PCR[POTENTIOMETER_C]  &=~PORT_PCR_MUX_MASK;
    IP_PORTC->PCR[POTENTIOMETER_C]    = PORT_PCR_MUX(0);

    IP_PORTD->PCR[GREEN_D]           &= ~PORT_PCR_MUX_MASK;
    IP_PORTD->PCR[GREEN_D]            = PORT_PCR_MUX(1);

    IP_PORTD->PCR[BLUE_D]            &= ~PORT_PCR_MUX_MASK;
    IP_PORTD->PCR[BLUE_D]             = PORT_PCR_MUX(1);

    IP_PORTD->PCR[RED_D]             &= ~PORT_PCR_MUX_MASK;
    IP_PORTD->PCR[RED_D]              = PORT_PCR_MUX(1);


    // IP_PTD->PDDR                    |= (1U<<BLUE_D);
    // IP_PTD->PDDR                    |= (1U<<GREEN_D);
    // IP_PTD->PDDR                    |= (1U<<RED_D);

 while(1)
    {
        /* Initiate new conversion by writing to ADC0_SC1A(ADCH) */
        /* ADCH = 12: External channel 12 as input */
        IP_ADC0->SC1[0] = ADC_SC1_ADCH(12);
        while(((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT) == 0);
        ADC_rawResult = IP_ADC0->R[0];

        if (range1 <= ADC_rawResult && ADC_rawResult <= range2) 
        {
            IP_PTD->PDDR    = (1U<<BLUE_D);
        } else if (range2 < ADC_rawResult && ADC_rawResult <= range3)
        {
            IP_PTD->PDDR    = (1U<<GREEN_D);
        } else if (range3 < ADC_rawResult && ADC_rawResult <= range4)
        {
            IP_PTD->PDDR    = (1U<<RED_D);
        }
    }

}

