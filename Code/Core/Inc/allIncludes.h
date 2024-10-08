/*
 * allIncludes.h
 *
 *  Created on: Sep 26, 2024
 *      Author: townl
 */

#ifndef SRC_ALLINCLUDES_H_
#define SRC_ALLINCLUDES_H_
//Pinout
#define ch1Out PA_4 //A3
#define ch2Out PA_5 //A4
#define i2cSDA PB_7 //D4
#define i2cSCL PB_6 //D5

#define channelSwitch PA_12 //D2
#define modeSwitch PB_0 //D3

#define freqKnobA PB_1 //D6
#define freqKnobB PA_8 //D9
#define ampKnobA PA_11 //D10
#define ampKnobB PB_5 //D11
#define shiftKnobA PA_7 //A6
#define shiftKnobB PA_6 //

//Constants
#define M_PI 3.14159


//Variables
#define DISPLAY_QUEUE_SIZE 3
#define INPUT_QUEUE_SIZE 3
#define SIGNAL_QUEUE_SIZE 3
#define QUEUE_BUFFER_SIZE 2 //currently only the semaphore is using this

//SSD1306 setup
#define SSD1306Address 0x3C<<1           // SSD1306 I2C address
#define SSD1306VerticalRes 64           //64 pixels tall
#define SSD1306HorizontalRes 128    //128 pixels across
#define SSD1306Pages SSD1306VerticalRes/8 //each page is a vertical 8 bits


#define waveFormRes 255 //how many steps per wavelength

#define FCLK 80000000UL //system clock speed

#define timerPSC 0 //timer prescaling value

#define squareLength waveFormRes / 2
#define pulseLenght waveFormRes / 12


//Core includes
#include "main.h"







enum WaveShape{SINE, SQUARE, PULSE, ECHO};

struct inputValues
	{
		int8_t Switch;
		bool isButtonPressed;
		int8_t AmpKnob1;
		int8_t FreqKnob1;
		int8_t AmpKnob2;
		int8_t FreqKnob2;
		int8_t DelayKnob2;
	};

struct signalInfo{
	uint32_t signalLocations[waveFormRes] = {0}; //the data array to be written
	uint32_t frequency = 0; //signal was tested to 80khz, 65k is not enough
	uint16_t amp = 0; //0-3.3 represented as 0 -4095
	uint8_t shiftAmount = 0; //shift amount from - 255
	WaveShape wave = SINE;
};

struct displayInfo{
	signalInfo *ChannelAInfo;
	signalInfo *ChannelBInfo;
};


#include "queue.h"
struct dacSetup{
	DAC_HandleTypeDef *hdacI;
	uint32_t DacChannel1I;
	TIM_HandleTypeDef *timer1I;
	signalQueue *channel1I;
};



//Our includes
#include "math.h"
#include "font.h"

#include "olivia.h"
#include "nathan.h"


#include "shane.h"



#endif /* SRC_ALLINCLUDES_H_ */
