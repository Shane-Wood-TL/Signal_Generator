/*
 * structsAndEnums.h
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#ifndef INC_SHANE_STRUCTSANDENUMS_H_
#define INC_SHANE_STRUCTSANDENUMS_H_

#include "allIncludes.h"

/**
 * @enum WaveShape
 * @brief Contains the different types of possible waves to generate
 *
 * @details WaveShape has the following options: SINE, SQUARE, PULSE, ECHO
 * ECHO can only be used on ch2
 */
enum WaveShape{SINE, SQUARE, PULSE, ECHO};

/**
 * @enum letterMappings
 * @brief Contains the available chars to display to the display
 *
 * @details Contains 0-9, A,m,p, F,r,e,q, S,h,i,f,t and a decimal point
 */
enum letterMappings{l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,A,F,S,e,f,h,i,m,p,q,r,t,ldecimal};

/**
 * @struct inputValues
 * @brief contains the values to be enqueued from the input driver
 *
 * @details Holds the status of a switch, button, and 3 knobs
 */
struct inputValues
	{
		int8_t Switch; ///< current logic level of the switch input
		bool isButtonPressed; ///< is true on edges of the button input
		int8_t AmpKnob; ///< is 1 on increase, -1 on decrease, and 0 on no change for the amplitude knob input
		int8_t FreqKnob; ///< is 1 on increase, -1 on decrease, and 0 on no change for the frequency knob input
		int8_t DelayKnob; ///< is 1 on increase, -1 on decrease, and 0 on no change for the delay/shift knob input
	};

/**
 * @struct signalInfo
 * @brief contains the values to be enqueued from the application layer to the outputDriver
 *
 * @details holds info for a waveform and the waveform itself
 */
struct signalInfo{
	uint32_t signalLocations[waveFormRes] = {0}; ///< the data array to be written
	uint16_t frequency = 0; ///< Max of 1k, uint16 is fine
	uint16_t amp = 0; ///< 0-3.3 represented as 0 -4095
	uint16_t shiftAmount = 0; ///< shift amount from - 256
	WaveShape wave = SINE; ///< Type of wave to be shown on screen
};

/**
 * @struct displayInfoValues
 * @brief contains the values to be enqueued from the outputDriver to the display
 *
 * @details Holds the info for frequency, amp, wave type for both channels, and shift for channelb
 */
struct displayInfoValues{
	uint16_t Afrequency = 0; ///< signal was tested to 80khz, 65k is not enough
	uint16_t Aamp = 0; ///< 0-3.3 represented as 0 -4095
	WaveShape Awave = SINE; ///< Wave type for ch1
	uint16_t Bfrequency = 0;///< Max of 1k, uint16 is fine, ch2 freq
	uint16_t Bamp = 0; ///< 0-3.3 represented as 0 -4095 for ch2
	uint16_t BshiftAmount = 0; ///< shift amount from - 256 for ch2
	WaveShape Bwave = SINE;///< Wave type for ch2
};

/**
 * @struct ssd1306Setup
 * @brief Contains the values used to set up the display
 *
 * @details Holds the screen's resolution, SPI D/C and RST pins and ports
 */
struct ssd1306Setup{
	uint8_t SSD1306VerticalR; ///< displays vertical resolution in pixels
	uint8_t SSD1306HorizontalR;///< displays horizontal resolution in pixels
	GPIO_TypeDef *dcPortI; ///< gpio port connected to D/C
	uint8_t dcPinI; ///< gpio pin for the pin connected to D/C
	GPIO_TypeDef *rstPortI; ///< gpio port for the pin connected to rst
	uint8_t rstPinI; ///< gpio pin connected to rst
};

#endif /* INC_SHANE_STRUCTSANDENUMS_H_ */
