/*
 * driver_clock.h
 *
 *  Created on: 30 Sept 2025
 *      Author: DUONG
 */

#ifndef DRIVER_HEADER_DRIVER_CLOCK_H_
#define DRIVER_HEADER_DRIVER_CLOCK_H_

#include "S32K144.h"

void init_SOSC_8MHz(void);
void init_SPLL_160Mhz(void);
void normal_SPLL_run_80MHz(void);

#endif /* DRIVER_HEADER_DRIVER_CLOCK_H_ */
