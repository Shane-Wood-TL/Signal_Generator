/*
 * allIncludes.h
 *
 *  Created on: Sep 26, 2024
 *      Author: townl
 */

#ifndef SRC_ALLINCLUDES_H_
#define SRC_ALLINCLUDES_H_


//Variables
#define waveFormRes 255 //how many steps per wavelength

//Device Setup
#define FCLK 80000000UL //system clock speed
#define timerPSC 0 //timer prescaling value

#define maxFreq 1000
#define minFreq 1

#define maxAmp 4095
#define minAmp 1

#define maxShift 255
#define minShift 0


//Pin definitions
#include "pinout.h"


//C includes
#include <cassert>

//Core STM includes
#include "main.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_utils.h"

//Our includes

//structures and enum definitions (shared)
#include "structsAndEnums.h"

//Shane's Files
#include "Shane/queue.h"
#include "Shane/font.h"
#include "Shane/display.h"
#include "Shane/memoryBarrier.h"
#include "Shane/dacDriver.h"
#include "Shane/outputDriver.h"

//Olivia's Files
#include "olivia.h"

//Nathan's Files
#include "nathan.h"


#endif /* SRC_ALLINCLUDES_H_ */
