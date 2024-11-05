/*
 * structsAndEnums.h
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#ifndef INC_SHANE_STRUCTSANDENUMS_H_
#define INC_SHANE_STRUCTSANDENUMS_H_

#include "allIncludes.h"

enum WaveShape{SINE, SQUARE, PULSE, ECHO};
enum letterMappngs{l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,A,F,S,e,f,h,i,m,p,q,r,t,ldecimal};

struct inputValues
	{
		int8_t Switch; //current logic level of the switch input
		bool isButtonPressed; //is true on edges of the button input
		int8_t AmpKnob; //is 1 on increase, -1 on decrease, and 0 on no change for the amplitude knob input
		int8_t FreqKnob; //is 1 on increase, -1 on decrease, and 0 on no change for the frequency knob input
		int8_t DelayKnob; //is 1 on increase, -1 on decrease, and 0 on no change for the delay/shift knob input
	};

struct signalInfo{
	uint32_t signalLocations[waveFormRes] = {0}; //the data array to be written
	uint16_t frequency = 0; //signal was tested to 80khz, 65k is not enough
	uint16_t amp = 0; //0-3.3 represented as 0 -4095
	uint16_t shiftAmount = 0; //shift amount from - 255
	WaveShape wave = SINE;
};

struct displayInfoValues{
	uint16_t Afrequency = 0; //signal was tested to 80khz, 65k is not enough
	uint16_t Aamp = 0; //0-3.3 represented as 0 -4095
	WaveShape Awave = SINE;
	uint16_t Bfrequency = 0; //signal was tested to 80khz, 65k is not enough
	uint16_t Bamp = 0; //0-3.3 represented as 0 -4095
	uint8_t BshiftAmount = 0; //shift amount from - 255
	WaveShape Bwave = SINE;
};



#endif /* INC_SHANE_STRUCTSANDENUMS_H_ */
