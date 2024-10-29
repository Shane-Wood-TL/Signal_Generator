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

struct displayInfoValues{
	uint32_t Afrequency = 0; //signal was tested to 80khz, 65k is not enough
	uint16_t Aamp = 0; //0-3.3 represented as 0 -4095
	WaveShape Awave = SINE;
	uint32_t Bfrequency = 0; //signal was tested to 80khz, 65k is not enough
	uint16_t Bamp = 0; //0-3.3 represented as 0 -4095
	uint8_t BshiftAmount = 0; //shift amount from - 255
	WaveShape Bwave = SINE;
};



#endif /* INC_SHANE_STRUCTSANDENUMS_H_ */
