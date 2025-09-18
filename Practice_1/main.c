/**
 * @file main.c
 * @author Duong Nguyen Nguyen
 * @brief 
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdint.h>
// <page 619>
#define PCC_BASE_R (0x40065000UL)
// <pape 684>
#define PCC_PORTC_OFFSET (0x12CUL)
// use to pcc access to PORTC
#define PCC_PORTC_R (*(volatile unsigned int *) (PCC_BASE_R + PCC_PORTC_OFFSET))
// set 1 to bit 31 CGC <Clock Gate Control>
#define PCC_CGC_MASK (1U<<30)

#define PORTC_PCR3 (*(volatile unsigned int *) (0x4004B012UL))
// set MUX as GPIO for PORTC_PCR3
#define PCR3_MUX_8_MASK (1U<<8)
#define PCR3_MUX_9_MASK (1U<<9)
#define PCR3_MUX_10_MASK (1U<<10)
/**
 * @brief GPIOC_PDDR register address
 *
 * GPIO C base address = 0x400FF080
 * PDDR (Port Data Direction Register) offset = 0x14
 * => Full address = 0x400FF080 + 0x14
 *
 * This register configures each pin of Port C
 * as input (0) or output (1).
 */
#define GPIOC_PDDR (*(volatile unsigned int *) (0x400FF080UL + 0x14UL))
/**
 * @brief GPIOC_PTOR register address
 *
 * GPIO C base address = 0x400FF080
 * PTOR (Port Toggle Output Register) offset = 0xC
 * => Full address = 0x400FF080 + 0xC
 *
 * This register configures each pin of Port C
 * as don't change (0) or output (1).
 */
#define GPIOC_PTOR (*(volatile unsigned int *) (0x400FF080UL + 0xCUL))

#define GPIOC_PIN3_MASK (1U<<3)

/**
 * @brief Delay function 
 * 
 * @param count 
 */
void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop"); 
    }
}

int main(void) {
/**
 * @brief 
 * 
 */
	PCC_PORTC_R |= PCC_CGC_MASK;
/**
 * @brief 001 -> PORT C MUX to alternative mode (GPIO)
 * 
 */
	PORTC_PCR3 |= PCR3_MUX_8_MASK;
	PORTC_PCR3 &= ~PCR3_MUX_9_MASK;
	PORTC_PCR3 &= ~PCR3_MUX_10_MASK;
/**
 * @brief set PDDR of GPIOC PIN 3 as OUTPUT 
 * 
 */
	GPIOC_PDDR |= GPIOC_PIN3_MASK;
/**
 * @brief While loop for pin 3 on
 * 
 */
	while (1)
	{
		GPIOC_PTOR |= GPIOC_PIN3_MASK;
		delay(1000000);
	}
	


    return 0;
}


