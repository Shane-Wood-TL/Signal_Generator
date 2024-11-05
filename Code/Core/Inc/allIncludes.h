/*
 * @file allIncludes.h
 * @brief This file contains all defines and includes for the entire project
 *
 *  Created on: Sep 26, 2024
 *      Author: Shane Wood
 */

#ifndef SRC_ALLINCLUDES_H_
#define SRC_ALLINCLUDES_H_


//Variables
#define waveFormRes 256 //how many steps per wavelength
#define squareLength waveFormRes / 2
#define pulseLenght waveFormRes / 12
//Device Setup
#define FCLK 72000000UL //system clock speed
#define timerPSC 4 //timer prescaling value

#define maxFreq 1000
#define minFreq 1

#define maxAmp 4095
#define minAmp 1

#define maxShift 256
#define minShift 0

//queue sizes
#define DISPLAY_QUEUE_SIZE 3
#define INPUT_QUEUE_SIZE 3
#define SIGNAL_QUEUE_SIZE 3
#define QUEUE_BUFFER_SIZE 2 //currently only the semaphore is using this

//Pin definitions
#include "pinout.h"


//C includes
#define assert(x) while(!(x))

//SSD1306 setup
#define SSD1306VerticalRes 64           //64 pixels tall
#define SSD1306HorizontalRes 128    //128 pixels across{}

//Core STM includes
#include "main.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_utils.h"

//Our includes

#define TOGGLE GPIOB->ODR ^= (1<<4);
#define WRITEON GPIOB->ODR |= (1<<4);
#define WRITEOFF GPIOB->ODR &= ~(1<<4);
//structures and enum definitions (shared)
#include "structsAndEnums.h"

//Shane's Files
#include "Shane/queue.h"
#include "Shane/font.h"
#include "Shane/display.h"
#include "Shane/dacDriver.h"
#include "Shane/outputDriver.h"

//Olivia's Files
#include "olivia.h"

//Nathan's Files
#include "nathan.h"

//Shane's Files
#include "Shane/memoryBarrier.h" //needs semaphore class

#endif /* SRC_ALLINCLUDES_H_ */
