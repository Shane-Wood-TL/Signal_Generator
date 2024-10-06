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

//Variables
#define QUEUE_BUFFER_SIZE 3

//SSD1306 setup
#define SSD1306Address 0x3C<<1           // SSD1306 I2C address
#define SSD1306VerticalRes 64           //64 pixels tall
#define SSD1306HorizontalRes 128    //128 pixels across
#define SSD1306Pages SSD1306VerticalRes/8 //each page is a vertical 8 bits


#define scopeRes 255
#define FCLK 80000000
#define timerPSC 0

#define squareLength scopeRes / 2
#define pulseLenght scopeRes / 12


//Core includes
#include "main.h"
#include "font.h"

enum WaveShape{SINE, SQUARE, PULSE, ECHO};

struct inputValues
	{
		bool ChannelSel;
		uint8_t ModeSel;
		uint32_t AmpValue1;
		uint32_t FreqValue1;
		uint32_t AmpValue2;
		uint32_t FreqValue2;
		uint32_t DelayValue2;
	};

struct signalInfo{
	uint32_t signalLocations[scopeRes] = {0}; //the data array to be written
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
#include "math.h"
#define M_PI 3.14159



struct dacSetup{
	DAC_HandleTypeDef *hdacI;
	uint32_t DacChannel1I;
	TIM_HandleTypeDef *timer1I;
	signalQueue *channel1I;
};

//Our includes
#include "olivia.h"
#include "nathan.h"


#include "shane.h"
#include "16pixelFont.h"


#endif /* SRC_ALLINCLUDES_H_ */
